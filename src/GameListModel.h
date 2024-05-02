#pragma once
#include <QAbstractListModel>
#include "Game.h"

class GameListModel : public QAbstractListModel {
  Q_OBJECT
public:
  enum { ReleaseYearRole = Qt::UserRole + 2 };
  GameListModel(QObject *parent = nullptr);
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
private slots:
  void updateList();
private:
  QList<Game> *games;
};