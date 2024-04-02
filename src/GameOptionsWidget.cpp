#include "GameOptionsWidget.h"
#include <QTextEdit>

GameOptionsWidget::GameOptionsWidget(QWidget *parent) : QWidget(parent) {
  init();
}

GameOptionsWidget::GameOptionsWidget(const Game game, QWidget *parent)
    : QWidget(parent) {
  init(game);
}

void GameOptionsWidget::init(const Game &game) {
  QWidget *gameInfo = new QWidget(this);
  name = new GameOptionWidget("Name: ", game.getName());
  working_directory = new GameOptionWidget(
      "Working directory: ", game.getWorkingDirectory(), false);
  exec = new GameOptionWidget("Executable: ", game.getExecutable(), true);
  save_path = new GameOptionWidget("Save path: ", game.getSavePath(), false);
  choose = new ChoosePictureWidget(game.getHeaderPath());
  GameOptionWidget *releaseYear = new GameOptionWidget(
      "Release year: ",
      game.getReleaseYear() == 0 ? "" : QString::number(game.getReleaseYear()));

  applyButton = new QPushButton("Apply");
  connect(applyButton, &QPushButton::clicked, this, &GameOptionsWidget::apply);
  applyButton->setDefault(true);
  applyButton->setDisabled(true);

  QPushButton *cancel = new QPushButton("Cancel");
  connect(cancel, &QPushButton::clicked, this, &GameOptionsWidget::closeWin);

  QHBoxLayout *HBL = new QHBoxLayout;
  HBL->addWidget(cancel);
  HBL->addWidget(applyButton);

  QVBoxLayout *VBL = new QVBoxLayout;
  QHBoxLayout *HBL1 = new QHBoxLayout;
  HBL1->addWidget(choose, Qt::AlignHCenter);
  VBL->addLayout(HBL1);
  VBL->addWidget(name);
  VBL->addWidget(releaseYear);
  gameInfo->setLayout(VBL);
  QVBoxLayout *VBL2 = new QVBoxLayout;
  QWidget *gameOptions = new QWidget(this);

  VBL2->addWidget(working_directory);
  VBL2->addWidget(exec);
  VBL2->addWidget(save_path);
  gameOptions->setLayout(VBL2);

  QTabWidget *tabWidget = new QTabWidget(this);

  tabWidget->addTab(gameInfo, "Game info");
  tabWidget->addTab(gameOptions, "Game options");

  QVBoxLayout *VBL3 = new QVBoxLayout;
  VBL3->addWidget(tabWidget);
  VBL3->addLayout(HBL);
  setLayout(VBL3);
  setWindowModality(Qt::ApplicationModal);
}

void GameOptionsWidget::closeWin() { close(); }