//
// Created by Oleksandr Leonov on 2024-07-14.
//

#pragma once
#include <QFutureWatcher>
#include <QSqlDatabase>
#include "Game.h"

class GameScanner : public QObject {
    Q_OBJECT

public:
    explicit GameScanner(QObject* parent = nullptr);
    void scanDirectory(const QString& path);

signals:
    void gamesFound(const QList<Game>& games);

private slots:
    void finishedScan();

private:
    QVariant getValueFromDB(const QString& table, const QString& variable, const int& id);
    static QString getAbsolutePath(const QString& path);

    QFutureWatcher<void> watcher;
    QMap<int, QString> gamesMap{};
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
};