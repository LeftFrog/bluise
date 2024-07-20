#include "GameOptionsWidget.h"
#include "../BluiseCore/bluise.h"

GameOptionsWidget::GameOptionsWidget(QWidget *parent) : QWidget(parent) {
  init();
}

GameOptionsWidget::GameOptionsWidget(const Game& game, QWidget *parent)
    : QWidget(parent) {
  init(game);
}

void GameOptionsWidget::init(const Game& game) {
    initOptions(game);
    setupConnections();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(createTabWidget());
    layout->addLayout(createButtons());
    setLayout(layout);

    setWindowModality(Qt::ApplicationModal);
    resize(700, 500);
}

void GameOptionsWidget::initOptions(const Game& game) {
    options["name"] = new GameOptionWidget("Name: ", game.getName());
    options["exec"] = new GameOptionWidget("Executable: ", game.getExecutable(), true);
    options["workingDirectory"] = new GameOptionWidget("Working directory: ", game.getWorkingDirectory(), false);
    options["savePath"] = new GameOptionWidget("Save path: ", game.getSavePath(), false);
    options["releaseYear"] = new GameOptionWidget("Release year: ", game.getReleaseYear() == 0 ? "" : QString::number(game.getReleaseYear()));
    choose = new ChoosePictureWidget(game.getCoverPath());
    runner = new BoxOptionWidget("Runner: ", game.getRunner(), this);
}

void GameOptionsWidget::setupConnections() {
    for(auto &option : options) {
        connect(option, &GameOptionWidget::gameChanged, this, &GameOptionsWidget::changed);
    }
    connect(choose, &ChoosePictureWidget::changed, this, &GameOptionsWidget::changed);
    connect(runner, &BoxOptionWidget::changed, this, &GameOptionsWidget::changed);
}

QLayout* GameOptionsWidget::createButtons() {
    applyButton = new QPushButton("Apply");
    connect(applyButton, &QPushButton::clicked, this, &GameOptionsWidget::apply);
    applyButton->setDefault(true);
    applyButton->setDisabled(true);

    QPushButton *cancel = new QPushButton("Cancel");
    connect(cancel, &QPushButton::clicked, this, &GameOptionsWidget::close);

    QHBoxLayout *HBL = new QHBoxLayout;
    HBL->addWidget(cancel);
    HBL->addWidget(applyButton);

    return HBL;
}

QTabWidget* GameOptionsWidget::createTabWidget() {
    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->addTab(createGameInfoWidget(), "Game info");
    tabWidget->addTab(createGameOptionsWidget(), "Game options");
    return tabWidget;
}

QWidget* GameOptionsWidget::createGameInfoWidget() {
    QWidget* gameInfo = new QWidget(this);

    QVBoxLayout* VBL = new QVBoxLayout;
    QHBoxLayout* HBL = new QHBoxLayout;

    HBL->addWidget(choose, Qt::AlignHCenter);
    VBL->addLayout(HBL);
    VBL->addWidget(options["name"]);
    VBL->addWidget(runner);
    VBL->addWidget(options["releaseYear"]);
    gameInfo->setLayout(VBL);

    return gameInfo;
}

QWidget* GameOptionsWidget::createGameOptionsWidget() {
    QVBoxLayout* VBL = new QVBoxLayout;
    QWidget* gameOptions = new QWidget(this);
    VBL->addWidget(options["workingDirectory"]);
    VBL->addWidget(options["exec"]);
    VBL->addWidget(options["savePath"]);
    gameOptions->setLayout(VBL);
    return gameOptions;
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
  QString path = DOCS + "res/covers/";
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
                          (DOCS + "res/covers").toStdString());
    header = fileName + extension;
  }
  return header;
}
