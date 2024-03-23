#pragma once
#include "GameOptionsWidget.h"

class GameAddWidget : public GameOptionsWidget {
  Q_OBJECT
public:
  GameAddWidget(QWidget *parent = nullptr);
protected slots:
  virtual void apply() override;
  void changed();
};