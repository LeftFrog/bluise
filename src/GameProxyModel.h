#pragma once
#include <QSortFilterProxyModel>

class GameProxyModel : public QSortFilterProxyModel {
  Q_OBJECT
public:
  GameProxyModel(QObject *parent = nullptr);
};