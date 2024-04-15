#include "GameProxyModel.h"

GameProxyModel::GameProxyModel(QObject *parent) : QSortFilterProxyModel(parent) {
  setDynamicSortFilter(true);
  setFilterCaseSensitivity(Qt::CaseInsensitive);
}