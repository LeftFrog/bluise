#include "AddGameWidget.h"
#include "AddLocalInstalledGameWidget.h"

AddGameWidget::AddGameWidget(QWidget* parent) : QWidget(parent) {
  layout = new QStackedLayout();

  QPushButton* addLocalInstalledGame = new QPushButton("Add a local installed game");
  connect(addLocalInstalledGame, &QPushButton::clicked, this, &AddGameWidget::addLocalGame);
  QPushButton* searchGames = new QPushButton("Search games on the hard drive");

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
  connect(wid, &AddLocalInstalledGameWidget::closed, this, &AddGameWidget::close);
  layout->addWidget(wid);
  layout->setCurrentIndex(1);
}