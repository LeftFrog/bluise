#pragma once
#include "ChoosePictureWidget.h"
#include "Game.h"
#include "GameOptionWidget.h"
#include <QPushButton>
#include <QTabWidget>
//  #include <QMap>

class GameOptionsWidget : public QWidget {
  Q_OBJECT
public:
  GameOptionsWidget(QWidget *parent = nullptr);
  GameOptionsWidget(const Game game, QWidget *parent = nullptr);

protected:
  void init(const Game& game = Game());
  ChoosePictureWidget *choose;
  QPushButton *applyButton;
  QMap<QString, GameOptionWidget*> options;
  QString setCover();
protected slots:
  void closeWin();
  virtual void apply() = 0;
};