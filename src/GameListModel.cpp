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
    // return games[index.row()].getHeader().scaled(390, 234, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    return games->at(index.row()).getCover();  // .scaled(265, 376, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
  } else if(role == Qt::DecorationRole) {
    return games->at(index.row()).getCover();
  } else if(role == Qt::UserRole + 1) {
    Game* g = &games->operator[](index.row());
    return QVariant::fromValue(g);
  }
  else {
    return QVariant();
  }
}

Qt::ItemFlags GameListModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::ItemIsEnabled;
  return QAbstractListModel::flags(index);
}