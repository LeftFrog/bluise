#pragma once
#include <QWidget>
#include <QLabel>
#include "Game.h"

class GameInfoWidget : public QWidget {
  Q_OBJECT
public:
  GameInfoWidget(QWidget *parent = nullptr);
public slots:
  void setGame(const QModelIndex& index);
private:
  Game* game;
  QLabel *name;
};