#pragma once
#include "GameOptionsWidget.h"

class EditGameWidget : public GameOptionsWidget {
  Q_OBJECT

public:
  EditGameWidget(const Game& game, QWidget *parent = nullptr);
signals:
  void gameChanged();
protected slots:
  virtual void apply() override;
  void changed() override;

private:
  bool optionsHaveChanged();
  const Game game;
};