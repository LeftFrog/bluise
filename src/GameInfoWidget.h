#pragma once
#include <QQuickWidget>
#include <QLabel>
#include "Game.h"
#include <QMenu>

class GameInfoWidget : public QQuickWidget {
  Q_OBJECT
public:
  GameInfoWidget(QWidget *parent = nullptr);
public slots:
  void setGame(const QModelIndex& index);
protected:
  void resizeEvent(QResizeEvent *event) override;
private slots:
  void play();
  void settings();
  void popupMenu();
private:
  Game *game;
  QMenu *menu;
};