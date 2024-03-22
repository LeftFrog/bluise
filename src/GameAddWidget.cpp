#include "GameAddWidget.h"
#include <QFile>
#include <filesystem>

GameAddWidget::GameAddWidget(QWidget *parent) : QWidget(parent) {
  name = new GameOptionWidget("Name", "", this);
  working_directory =
      new GameOptionWidget("Working directory", "", false, this);
  exec = new GameOptionWidget("Executable", "", true, this);
  save_path = new GameOptionWidget("Save path", "", false, this);
  choose = new ChoosePictureWidget("", this);
  QVBoxLayout *VBL = new QVBoxLayout;
  VBL->addWidget(choose);
  VBL->addWidget(name);
  VBL->addWidget(working_directory);
  VBL->addWidget(exec);
  VBL->addWidget(save_path);
  setLayout(VBL);

  QPushButton *cancel = new QPushButton("Cancel");
  connect(cancel, &QPushButton::clicked, this, &GameAddWidget::closeWin);
  addButton = new QPushButton("Add");
  connect(addButton, &QPushButton::clicked, this, &GameAddWidget::addGame);
}

void GameAddWidget::addGame() {
  std::filesystem::copy(choose->path().toStdString(),
                        (bluise_core::DOCS + "res/").toStdString());
  QString header = QFile(choose->path()).fileName();
  bluise_core::games.push_back(Game(name->text(), working_directory->text(),
                                    exec->text(), save_path->text(), header));
  close();
}
