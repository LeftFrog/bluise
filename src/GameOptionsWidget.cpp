#include "GameOptionsWidget.h"
#include <QTextEdit>

GameOptionsWidget::GameOptionsWidget(QWidget *parent) {
  name = new GameOptionWidget("Name: ", "");
  working_directory = new GameOptionWidget("Working directory: ", "", false);
  exec = new GameOptionWidget("Executable: ", "", true);
  save_path = new GameOptionWidget("Save path: ", "", false);
  choose = new ChoosePictureWidget("");

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
  VBL->addWidget(choose, Qt::AlignHCenter);
  VBL->addWidget(name);
  VBL->addWidget(working_directory);
  VBL->addWidget(exec);
  VBL->addWidget(save_path);
  VBL->addLayout(HBL);

  setLayout(VBL);

  setWindowModality(Qt::ApplicationModal);
}

GameOptionsWidget::GameOptionsWidget(const Game game, QWidget *parent) {
  name = new GameOptionWidget("Name: ", game.get_name());
  working_directory =
      new GameOptionWidget("Working directory: ", game.get_working_directory(), false);
  exec = new GameOptionWidget("Executable: ", game.get_executable(), true);
  save_path = new GameOptionWidget("Save path: ", game.get_save_path(), false);
  choose = new ChoosePictureWidget(game.get_header_path());

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
  VBL->addWidget(working_directory);
  VBL->addWidget(exec);
  VBL->addWidget(save_path);
  VBL->addLayout(HBL);

  setLayout(VBL);

  setWindowModality(Qt::ApplicationModal);
}

void GameOptionsWidget::closeWin() { close(); }