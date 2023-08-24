#pragma once
#include <QAbstractListModel> 
#include <QVector>
#include "QGame.h"
#include <QIcon>
#include <bluise.h>

class GameListModel : public QAbstractListModel {
Q_OBJECT
public:
    GameListModel(QObject* parent = nullptr);
    QVariant data(const QModelIndex& index, int role) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
private:
    QVector<QGame> games;
};