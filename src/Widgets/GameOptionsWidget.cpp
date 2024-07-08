#include "GameOptionsWidget.h"
#include <QTextEdit>
#include "../BluiseCore/bluise.h"

GameOptionsWidget::GameOptionsWidget(QWidget *parent) : QWidget(parent) {
  init();
}

GameOptionsWidget::GameOptionsWidget(const Game game, QWidget *parent)
    : QWidget(parent) {
  init(game);
}

void GameOptionsWidget::init(const Game &game) {
  QWidget *gameInfo = new QWidget(this);
  //options = QMap<QString, GameOptionWidget *>();
  options["name"] = new GameOptionWidget("Name: ", game.getName());
  options["exec"] = new GameOptionWidget("Executable: ", game.getExecutable(), true);
  options["workingDirectory"] = new GameOptionWidget(
    "Working directory: ", game.getWorkingDirectory(), false);
  options["savePath"] = new GameOptionWidget("Save path: ", game.getSavePath(), false);
  options["releaseYear"] = new GameOptionWidget("Release year: ", game.getReleaseYear() == 0 ? "" : QString::number(game.getReleaseYear()));
  choose = new ChoosePictureWidget(game.getCoverPath());

  runner = new BoxOptionWidget("Runner: ", game.getRunner(), this);

  applyButton = new QPushButton("Apply");
  connect(applyButton, &QPushButton::clicked, this, &GameOptionsWidget::apply);
  applyButton->setDefault(true);
  applyButton->setDisabled(true);

  QPushButton *cancel = new QPushButton("Cancel");
  connect(cancel, &QPushButton::clicked, this, &GameOptionsWidget::close);

  QHBoxLayout *HBL = new QHBoxLayout;
  HBL->addWidget(cancel);
  HBL->addWidget(applyButton);

  QVBoxLayout *VBL = new QVBoxLayout;
  QHBoxLayout *HBL1 = new QHBoxLayout;
  HBL1->addWidget(choose, Qt::AlignHCenter);
  VBL->addLayout(HBL1);
  VBL->addWidget(options["name"]);
  VBL->addWidget(runner);
  VBL->addWidget(options["releaseYear"]);
  gameInfo->setLayout(VBL);
  QVBoxLayout *VBL2 = new QVBoxLayout;
  QWidget *gameOptions = new QWidget(this);
  VBL2->addWidget(options["workingDirectory"]);
  VBL2->addWidget(options["exec"]);
  VBL2->addWidget(options["savePath"]);
  gameOptions->setLayout(VBL2);

  QTabWidget *tabWidget = new QTabWidget(this);

  tabWidget->addTab(gameInfo, "Game info");
  tabWidget->addTab(gameOptions, "Game options");

  QVBoxLayout *VBL3 = new QVBoxLayout;
  VBL3->addWidget(tabWidget);
  VBL3->addLayout(HBL);

  for(auto &option : options) {
    connect(option, &GameOptionWidget::gameChanged, this, &GameOptionsWidget::changed);
  }
  connect(choose, &ChoosePictureWidget::changed, this,
          &GameOptionsWidget::changed);
  connect(runner, &BoxOptionWidget::changed, this, &GameOptionsWidget::changed);

  setLayout(VBL3);
  setWindowModality(Qt::ApplicationModal);
  resize(700, 500);
}

QString GameOptionsWidget::setCover() {
  QString header = "";
  QString fileName = QString::fromStdString(
      std::filesystem::path(choose->path().toStdString())
          .filename()
          .string()
          .substr(0, std::filesystem::path(choose->path().toStdString())
                              .filename()
                              .string()
                              .size() -
                          4));
  QString extension = QString::fromStdString(
      std::filesystem::path(choose->path().toStdString())
          .filename()
          .string()
          .substr(std::filesystem::path(choose->path().toStdString())
                      .filename()
                      .string()
                      .size() -
                  4));
  QString path = bluise_core::DOCS + "res/covers/";
  if (QFile::exists(path + fileName + extension)) {
    int i = 1;
    while (QFile::exists(path + fileName + QString::number(i) + extension)) {
      ++i;
    }
    std::filesystem::copy(
        choose->path().toStdString(),
        (path + fileName + QString::number(i) + extension).toStdString());
    header = fileName + QString::number(i) + extension;
  } else {
    std::filesystem::copy(choose->path().toStdString(),
                          (bluise_core::DOCS + "res/covers").toStdString());
    header = fileName + extension;
  }
  return header;
}