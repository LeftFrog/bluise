#include "GameListModel.h"

QVariant GameListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() > bluise_core::games.size() || index.row() < 0) {
        return QVariant();
    }
    return (role == Qt::DisplayRole || role == Qt::EditRole) ? (bluise_core::games[index.row()].get_name().c_str()) : QVariant();
}

int GameListModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid()) {
        return 0;
    }
    return bluise_core::games.size();
}

Qt::ItemFlags GameListModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractListModel::flags(index);
    return index.isValid() ? (flags | Qt::ItemIsEditable) : flags;
}
