#pragma once
#include "ChoosePictureWidget.h"
#include "GameOptionWidget.h"
#include "bluise.h"
#include <QPushButton>
#include <QWidget>

class GameAddWidget : public QWidget {
  Q_OBJECT
private:
  GameOptionWidget *name;
  GameOptionWidget *working_directory;
  GameOptionWidget *exec;
  GameOptionWidget *save_path;
  ChoosePictureWidget *choose;
  QPushButton *addButton;
private slots:
  void closeWin() { close(); }
  void addGame();

public:
  GameAddWidget(QWidget *parent = nullptr);
};