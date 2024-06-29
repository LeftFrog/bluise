#pragma once
#include "GameOptionsWidget.h"

class EditGameWidget : public GameOptionsWidget {
  Q_OBJECT

public:
  EditGameWidget(Game *_game, QWidget *parent = nullptr);
signals:
  void gameChanged();
protected slots:
  virtual void apply() override;
  void changed() override;

private:
  bool optionsHaveChanged();
  Game *game;
};