#pragma once
#include <QListView>
#include <QAbstractItemModel>
#include "GameDelegate.h"

class GameListView : public QListView {
    Q_OBJECT
public:
    explicit GameListView(QAbstractItemModel *model = nullptr, QWidget *parent = nullptr);
};