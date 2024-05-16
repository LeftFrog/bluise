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
  QString pattern = nameRegularExpression.trimmed()+"(\\w+\\s*)*+:"+filterRegularExpression;
  QRegularExpression regex(pattern, QRegularExpression::CaseInsensitiveOption);
  setFilterRegularExpression(regex/*(\\w+\\s*)+"(\\w+\\s*)+:"+filterRegularExpression*/);
}