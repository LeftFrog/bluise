#pragma once
#include <QScrollArea>
#include "AddWidget.h"

class GameScrollArea : public QScrollArea {
  Q_OBJECT
public:
  GameScrollArea(QWidget *parent = nullptr);
protected:
  virtual void resizeEvent(QResizeEvent *event) override;
private:
  AddWidget* addWidget;
};