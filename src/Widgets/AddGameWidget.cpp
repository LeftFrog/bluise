#include "AddGameWidget.h"
#include "AddLocalInstalledGameWidget.h"
#include "ScanForGamesWidget.h"
#include <QTimer>

AddGameWidget::AddGameWidget(QWidget* parent) : QWidget(parent) {
  layout = new QStackedLayout();

  QPushButton* addLocalInstalledGame = new QPushButton("Add a local installed game");
  connect(addLocalInstalledGame, &QPushButton::clicked, this, &AddGameWidget::addLocalGame);
  QPushButton* searchGames = new QPushButton("Scan for games on the hard drive");
  connect(searchGames, &QPushButton::clicked, this, &AddGameWidget::scanForGames);
  QVBoxLayout* VBL = new QVBoxLayout();
  VBL->addWidget(addLocalInstalledGame);
  VBL->addWidget(searchGames);

  QWidget* options = new QWidget();
  options->setLayout(VBL);
  layout->addWidget(options);

  setLayout(layout);
}

void AddGameWidget::addLocalGame() {
  AddLocalInstalledGameWidget* wid = new AddLocalInstalledGameWidget();
  resize(700, 689);
  connect(wid, &AddLocalInstalledGameWidget::closed, this, &AddGameWidget::close);
  layout->addWidget(wid);
  layout->setCurrentIndex(1);
}

void AddGameWidget::scanForGames() {
  ScanForGamesWidget* wid = new ScanForGamesWidget();
  connect(wid, &ScanForGamesWidget::closed, this, &AddGameWidget::close);
  layout->addWidget(wid);
  layout->setCurrentIndex(1);
  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, wid, &ScanForGamesWidget::scan);
  timer->setSingleShot(true); // Run only once
  timer->start(10);
}