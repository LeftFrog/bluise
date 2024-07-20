#include "GameListModel.h"
#include <algorithm>

GameListModel::GameListModel(QObject *parent) : QAbstractListModel(parent) {
    games = {};
}

int GameListModel::rowCount(const QModelIndex &parent) const {
    return games.size();
}

QVariant GameListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();
    if (index.row() >= games.size()) return QVariant();
    if (role == Qt::DisplayRole) {
        return games.at(index.row()).getName();
    } else if(role == Qt::UserRole) {
        return games.at(index.row()).getCover();
    } else if(role == Qt::DecorationRole) {
        return games.at(index.row()).getCover();
    } else if(role == Qt::UserRole + 1) {
        return QVariant::fromValue((&games[index.row()]));
    } else if(role == ReleaseYearRole) {
        return games.at(index.row()).getReleaseYear();
    } else if(role == InstalledRole) {
        return games.at(index.row()).getName() + ":" + (games.at(index.row()).isDisabled() ? "t" : "f");
    } else {
        return QVariant();
    }
}

bool GameListModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid()) return false;
    if (index.row() >= games.size()) return false;
    try {
        if (role==NameRole) {
            games[index.row()].setName(value.toString());
            return true;
        } else if (role==ExecutableRole) {
            games[index.row()].setExecutable(value.toString());
        } else if (role==WorkingDirectoryRole) {
            games[index.row()].setWorkingDirectory(value.toString());
        } else if (role==SavePathRole) {
            games[index.row()].setSavePath(value.toString());
        } else if (role==CoverRole) {
            games[index.row()].setCover(value.toString());
        } else if (role==ReleaseYearRole) {
            games[index.row()].setReleaseYear(value.toInt());
        } else if (role==RunnerRole) {
            games[index.row()].setRunner(static_cast<Game::Runner>(value.toInt()));
        } else {
            return false;
        }
    } catch (...) {
        qDebug() << "Error setting data";
        return false;
    }
}

Qt::ItemFlags GameListModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::ItemIsEnabled;
    return QAbstractListModel::flags(index);
}

bool GameListModel::insertRows(int row, int count, const QModelIndex &parent) {
    beginInsertRows(parent, row, row + count - 1);
    endInsertRows();
    return true;
}

bool GameListModel::removeRows(int row, int count, const QModelIndex &parent) {
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    return true;
}

QVariant GameListModel::headerData(int section, Qt::Orientation orientation, int role) {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section) {
        case 0:
            return QString("Name");
        case 1:
            return QString("Icon");
        case 2:
            return QString("Date");
        default:
            return QVariant();
    }
}

void GameListModel::addGame(const Game& game) {
    beginInsertRows(QModelIndex(), games.size(), games.size());
    games.append(game);
    endInsertRows();
    std::sort(this->games.begin(), this->games.end());
}

void GameListModel::addGames(const QList<Game>& games) {
    beginInsertRows(QModelIndex(), this->games.size(), this->games.size()+games.size()-1);
    this->games.append(games);
    endInsertRows();
    std::sort(this->games.begin(), this->games.end());
}

void GameListModel::removeGame(const Game& game) {
    beginRemoveRows(QModelIndex(), games.indexOf(game), games.indexOf(game));
    games.removeOne(game);
    endRemoveRows();
}

QModelIndex GameListModel::indexOf(const Game& game) const {
    return index(games.indexOf(game));
}
