#pragma once
#include <QAbstractListModel>
#include "../BluiseCore/Game.h"

class GameListModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum {  CoverRole = Qt::UserRole,
            GameReferenceRole = Qt::UserRole + 1,
            ReleaseYearRole = Qt::UserRole + 2,
            InstalledRole = Qt::UserRole + 3,
            NameRole = Qt::DisplayRole,
            ExecutableRole = Qt::UserRole + 4,
            WorkingDirectoryRole = Qt::UserRole + 5,
            SavePathRole = Qt::UserRole + 6,
            RunnerRole = Qt::UserRole + 7,
            };
    GameListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole);

    void addGame(const Game& game);
    void addGames(const QList<Game>& games);
    void removeGame(const Game& game);

    QModelIndex indexOf(const Game& game) const;

    QList<Game> getGames() const { return games; }

private:
    QList<Game> games;
};