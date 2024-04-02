#pragma once
#include "ChoosePictureWidget.h"
#include "Game.h"
#include "GameOptionWidget.h"
#include <QPushButton>
#include <QTabWidget>

class GameOptionsWidget : public QWidget {
  Q_OBJECT
public:
  GameOptionsWidget(QWidget *parent = nullptr);
  GameOptionsWidget(const Game game, QWidget *parent = nullptr);

protected:
  void init(const Game& game = Game());
  GameOptionWidget *name;
  GameOptionWidget *working_directory;
  GameOptionWidget *exec;
  GameOptionWidget *save_path;
  ChoosePictureWidget *choose;
  QPushButton *applyButton;
protected slots:
  void closeWin();
  virtual void apply() = 0;
};