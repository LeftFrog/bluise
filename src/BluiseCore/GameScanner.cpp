//
// Created by Leonov Oleksandr on 2024-07-14.
//
#include "GameScanner.h"
#include <QtConcurrent>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include "bluise.h"
#include "Game.h"


GameScanner::GameScanner(QObject* parent) : QObject(parent) {
    db.setDatabaseName("games.db");
    if (!db.open()) {
        qDebug() << "Failed to open database";
    }

    connect(&watcher, &QFutureWatcher<void>::finished, this, &GameScanner::finishedScan);
}

QVariant GameScanner::getValueFromDB(const QString& table, const QString& variable, const int& id) {
    QSqlQuery query(db);
    QString idStr = table != "games" ? "game_id" : "id";
    query.prepare(QString("SELECT %1 FROM %2 WHERE %3 = :id").arg(variable).arg(table).arg(idStr));
    query.bindValue(":id", id);

    if (query.exec()) {}
    while (query.next()) {
        QSqlRecord record = query.record();
        QStringList list = variable.split(',');
        if(list.count()==1) {
            return QVariant(record.value(variable));
        }
        QList<QVariant> values;
        for (auto var : list) {
            values.append(QVariant(record.value(var)));
        }
        return QVariant(values);
    }
    return QVariant();
}

QString GameScanner::getAbsolutePath(const QString& path) {
    QString extendedPath = path;
    if(path.startsWith("~")) {
        extendedPath.replace("~", QDir::homePath());
    }
    return extendedPath;
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
                    gamesMap[query.value(0).toInt()] = info.filePath();
                }
            }
        }
    });
    watcher.setFuture(future);
}

void GameScanner::finishedScan() {

}