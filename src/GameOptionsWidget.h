#pragma once
#include "ChoosePictureWidget.h"
#include "Game.h"
#include "GameOptionWidget.h"
#include <QPushButton>
#include <QTabWidget>
#include <QComboBox>
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
  QComboBox *runnerBox;
  QString setCover();
  Game::Runner runner;
protected slots:
  virtual void applyRunner(const QString& _runner);
  void closeWin();
  virtual void apply() = 0;
};