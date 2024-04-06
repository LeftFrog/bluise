#pragma once
#include <QAbstractListModel>
#include "Game.h"

class GameListModel : public QAbstractListModel {
  Q_OBJECT
public:
  GameListModel(QObject *parent = nullptr);
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
private:
  QList<Game> *games;
};