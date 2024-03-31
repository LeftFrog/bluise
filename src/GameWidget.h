#pragma once
#include "Game.h"
#include <QQuickItem>
#include <QQuickWidget>


class GameWidget : public QQuickWidget {
  Q_OBJECT
public:
  GameWidget(Game *_game, QWidget *parent = nullptr);
  virtual QSize sizeHint() const override;
  bool operator>(const GameWidget &other) const;
  QString name() const { return game->get_name(); }
  int releaseYear() const { return game->getReleaseYear(); }
public slots:
  void edit();
  void play();
  void repaintSlot();
protected:
  virtual void resizeEvent(QResizeEvent *event) override;
private:
  Game *game;
};