#include "GameListModel.h"

GameListModel::GameListModel(QObject *parent)  : QAbstractListModel(parent) {
    for(auto game : bluise_core::games) {
        games.push_back(QGame(game.get_name(), game.get_working_directory(), game.get_executable(), game.get_save_path()));
    }
}

QVariant GameListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() > games.size() || index.row() < 0) {
        return QVariant();
    }
    if(role == Qt::DisplayRole || role == Qt::EditRole){
        return QString(games[index.row()].get_name().c_str());
    }
    else if(role == Qt::DecorationRole) {
        return games[index.row()].get_icon();
    }
    else {
        return QVariant();
    }
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
