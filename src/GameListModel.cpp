#include "GameListModel.h"
#include "Game.h"
#include "bluise.h"
#include <QImage>

GameListModel::GameListModel(QObject *parent) : QAbstractListModel(parent) {
  games = &bluise_core::games;
}

int GameListModel::rowCount(const QModelIndex &parent) const {
  return games->size();
}

QVariant GameListModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();
  if (index.row() >= games->size()) return QVariant();
  if (role == Qt::DisplayRole) {
    return games->at(index.row()).getName();
  } else if(role == Qt::UserRole) {
    return games->at(index.row()).getCover(); 
  } else if(role == Qt::DecorationRole) {
    return games->at(index.row()).getCover();
  } else if(role == Qt::UserRole + 1) {
    Game* g = &games->operator[](index.row());
    return QVariant::fromValue(g);
  } else if(role == ReleaseYearRole) {
    return games->at(index.row()).getReleaseYear();
  } else if(role == InstalledRole) {
    return games->at(index.row()).getName() + ":" +(games->at(index.row()).isDisabled() ? "t" : "f");
  }
  else {
    return QVariant();
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

void GameListModel::updateList() {
  insertRows(games->size()-1, 1);
}

// QVariant GameListModel::headerData(int section, Qt::Orientation orientation, int role) {

// }