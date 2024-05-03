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
  a.setWindowIcon(QIcon("/Users/leftfrog/Projects/bluise/res/1024-mac-1024.png"));
  MainWindow w;
  w.show();
  return a.exec();
}
