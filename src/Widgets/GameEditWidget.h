#pragma once
#include "GameOptionsWidget.h"

class GameEditWidget : public GameOptionsWidget {
  Q_OBJECT

public:
  GameEditWidget(Game *_game, QWidget *parent = nullptr);
signals:
  void gameChanged();
protected slots:
  virtual void apply() override;
  void changed() override;

private:
  bool optionsHaveChanged();
  Game *game;
};