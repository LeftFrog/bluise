#pragma once
#include <QAbstractListModel> 
#include <bluise.h>

class GameListModel : public QAbstractListModel {
Q_OBJECT
public:
    GameListModel(QObject* parent = nullptr) : QAbstractListModel(parent) {}
    QVariant data(const QModelIndex& index, int role) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
};