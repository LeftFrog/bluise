#pragma once
#include "GameWidget.h"
#include <QtWidgets>


class GameListWidget : public QWidget {
  Q_OBJECT
public:
  QList<GameWidget *> game_widgets;
  QList<GameWidget *> gameWidgetsProxy;
  GameListWidget(QWidget *parent = nullptr);
};