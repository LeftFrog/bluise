#pragma once
#include <QListView>
#include <QAbstractItemModel>

class GameListView : public QListView {
    Q_OBJECT
public:
    explicit GameListView(QAbstractItemModel *model = nullptr, QWidget *parent = nullptr);
};