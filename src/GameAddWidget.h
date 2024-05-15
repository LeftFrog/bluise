#pragma once
#include "GameOptionsWidget.h"

class GameAddWidget : public GameOptionsWidget {
  Q_OBJECT
public:
  GameAddWidget(QWidget *parent = nullptr);
signals:
  void added();
protected slots:
  virtual void apply() override;
  void changed() override;
};