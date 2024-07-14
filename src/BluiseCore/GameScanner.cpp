//
// Created by Leonov Oleksandr on 2024-07-14.
//
#include "GameScanner.h"
#include <QtConcurrent>
#include <QSqlQuery>


GameScanner::GameScanner(QObject* parent) : QObject(parent) {
    db.setDatabaseName("games.db");
    if (!db.open()) {
        qDebug() << "Failed to open database";
    }

    connect(&watcher, &QFutureWatcher<void>::finished, this, &GameScanner::finishedScan);
}

void GameScanner::scanDirectory(const QString& path) {
    QFuture<void> future = QtConcurrent::run([this, path] mutable{
        QDirIterator it(path, QStringList() << "*.app", QDir::Files | QDir::Dirs, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            QSqlQuery query(db);
            query.prepare("SELECT game_id FROM game_executables WHERE executable = :executable");
            QString file = it.next();
            QFileInfo info(file);
            query.bindValue(":executable", info.fileName());
            if(query.exec()) {
                if(query.next()) {
                    gameMap[query.value(0).toInt()] = info.filePath();
                }
            }
        }
    });
    watcher.setFuture(future);
}

void GameScanner::finishedScan() {
    qDebug() << "Finished scanning";
}