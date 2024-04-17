#include "bluise.h"
#include "invalid_path.h"
#include "GameListModel.h"
#include <iostream>
#include <QtWidgets>
#include "MainWindow.h"
#include "QListView" 
#include "BeautifulButton.h"

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
  BeautifulUi::BeautifulButton *button = new BeautifulUi::BeautifulButton(&w);
  button->setGeometry(10, 10, 40, 25);
  button->setIcon(QIcon::fromTheme("document-new"));
  QMenu *menu = new QMenu(button);
  menu->addAction("New Game");
  button->setMenu(menu);
  w.show();
  // } else {
  //   command_processor::process_command_line(argc, argv);
  // }
  return a.exec();
}
