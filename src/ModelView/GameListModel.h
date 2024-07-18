#pragma once
#include <QAbstractListModel>
#include "../BluiseCore/Game.h"

class GameListModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum { ReleaseYearRole = Qt::UserRole + 2,
           InstalledRole = Qt::UserRole + 3 };
    GameListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole);

    void addGame(const Game& game);
    void addGames(const QList<Game>& games);
    void removeGame(const Game& game);

    QList<Game> getGames() const { return games; }

public slots:
    void removeGame();
    void updateList();

private:
    QList<Game> games;
};