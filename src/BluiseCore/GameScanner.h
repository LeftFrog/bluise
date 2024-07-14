//
// Created by Oleksandr Leonov on 2024-07-14.
//

#pragma once
#include <QFutureWatcher>
#include <QSqlDatabase>

class GameScanner : public QObject {
    Q_OBJECT

public:
    explicit GameScanner(QObject* parent = nullptr);
    void scanDirectory(const QString& path);

private slots:
    void finishedScan();

private:
    QFutureWatcher<void> watcher;
    QMap<int, QString> gameMap{};
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
};