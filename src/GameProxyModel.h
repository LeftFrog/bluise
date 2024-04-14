#pragma once
#include <QAbstractProxyModel>

class GameProxyModel : public QAbstractProxyModel {
  Q_OBJECT
public:
  GameProxyModel(QObject *parent = nullptr);
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
};