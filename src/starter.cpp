#include "bluise.h"
#include "invalid_path.h"
#include "GameListModel.h"
#include <iostream>
#include <QtWidgets>
#include "MainWindow.h"
#include "QListView" 
#include "BeautifulButton.h"
#include "BeautifulButtonGroup.h"

void qt_win() {
  GameListModel model;
  QListView view;
  view.setModel(&model);
  view.show();
}

int main(int argc, char **argv) {
  QApplication a(argc, argv);
  bluise_core::readGamesJSON();
  // if (argc == 1) {
  QWidget w;
  BeautifulUi::BeautifulButtonGroup *group = new BeautifulUi::BeautifulButtonGroup(&w);
  BeautifulUi::BeautifulButton *button = new BeautifulUi::BeautifulButton(&w);
  button->setIcon(QIcon::fromTheme("document-new"));
  group->addButton(button);
  button = new BeautifulUi::BeautifulButton(&w);
  button->setIcon(QIcon::fromTheme("document-open"));
  group->addButton(button);
  w.show();
  // } else {
  //   command_processor::process_command_line(argc, argv);
  // }
  return a.exec();
}
