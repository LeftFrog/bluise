#pragma once
#include <QtWidgets>
#include "GameWidget.h"

class GameListWidget : public QWidget {
    Q_OBJECT
public:
    QList<GameWidget*> game_widgets;
    GameListWidget(QWidget *parent = nullptr);
};