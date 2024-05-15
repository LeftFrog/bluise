#pragma once
#include "ChoosePictureWidget.h"
#include "Game.h"
#include "GameOptionWidget.h"
#include <QPushButton>
#include <QTabWidget>
#include <QComboBox>
#include "BoxOptionWidget.h"

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
  BoxOptionWidget* runner;
protected slots:
  void closeWin();
  virtual void apply() = 0;
  virtual void changed() = 0;
};