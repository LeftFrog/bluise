#include "GameProxyModel.h"

GameProxyModel::GameProxyModel(QObject *parent) : QSortFilterProxyModel(parent) {
  setDynamicSortFilter(true);
  setFilterCaseSensitivity(Qt::CaseInsensitive);
  nameRegularExpression = "";
  filterRegularExpression = "";
}

void GameProxyModel::setNameExp(const QString& name) {
  nameRegularExpression = name;
  updateRegularExpression();
}

void GameProxyModel::setFilterExp(const QString& filter) {
  filterRegularExpression = filter;
  updateRegularExpression();
}

void GameProxyModel::updateRegularExpression() {
  setFilterRegularExpression(nameRegularExpression+"(\\w+\\s*)+:"+filterRegularExpression);
}