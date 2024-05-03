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
  // if (argc == 1) {
  // QWidget w;
  // fa::QtAwesome *awesome = new fa::QtAwesome(&w);
  // awesome->initFontAwesome();
  // BeautifulUi::BeautifulButtonGroup *group = new BeautifulUi::BeautifulButtonGroup(&w);
  // BeautifulUi::BeautifulButton *listView = new BeautifulUi::BeautifulButton(group);
  // BeautifulUi::BeautifulButton *tableView = new BeautifulUi::BeautifulButton(group);
  // tableView->setIcon(awesome->icon(fa::fa_styles::fa_solid, fa::fa_table_cells_large));
  // listView->setIcon(awesome->icon(fa::fa_styles::fa_solid, fa::fa_list_ul));
  // group->addButton(tableView);
  // group->addButton(listView);
  // BeautifulUi::BeautifulButtonGroup *group = new BeautifulUi::BeautifulButtonGroup(&w);
  // BeautifulUi::BeautifulButton *button = new BeautifulUi::BeautifulButton(group);
  // button->setIcon(QIcon::fromTheme("document-new"));
  // group->addButton(button);

  // button->setIcon(awesome->icon(fa::fa_solid, fa::fa_chevron_down));
  // group->addButton(new BeautifulUi::BeautifulButton(group));
  // w.show();
  // } else {
  //   command_processor::process_command_line(argc, argv);
  // }
  MainWindow w;
  w.show();
  return a.exec();
}
