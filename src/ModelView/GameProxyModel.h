#pragma once
#include <QSortFilterProxyModel>

class GameProxyModel : public QSortFilterProxyModel {
    Q_OBJECT

public:
    GameProxyModel(QObject* parent = nullptr);

public slots:
    void setNameExp(const QString& name);
    void setFilterExp(const QString& filter);

private:
    void updateRegularExpression();
    QString nameRegularExpression;
    QString filterRegularExpression;
};
