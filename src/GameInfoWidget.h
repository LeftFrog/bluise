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
private slots:
  void play();
  void settings();
private:
  Game* game;
  QLabel *name;
};