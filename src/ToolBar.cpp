#include "ToolBar.h"
#include <QPushButton>
#include <QMenu>
#include "QtAwesome/QtAwesome/QtAwesome.h"

ToolBar::ToolBar(QWidget *parent) : QWidget(parent) {
  // setMovable(false);
  // setFloatable(false);
  setFixedHeight(36);

  fa::QtAwesome *awesome = new fa::QtAwesome;
  awesome->initFontAwesome();

  QWidget *spacer = new QWidget;
  spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  group = new BeautifulUi::BeautifulButtonGroup(this);
  BeautifulUi::BeautifulButton *listView = new BeautifulUi::BeautifulButton(fa::fa_table_cells_large, group);
  BeautifulUi::BeautifulButton *tableView = new BeautifulUi::BeautifulButton(fa::fa_list_ul, group);
  group->addButton(tableView);
  group->addButton(listView);

  optionsButton = new BeautifulUi::BeautifulButton(fa::fa_ellipsis, this);
  QMenu *optionsMenu = new QMenu();
  optionsMenu->addAction("Options");
  optionsMenu->addAction("Show unistalled");
  optionsButton->setMenu(optionsMenu);

  search = new QLineEdit(this);
  search->setStyleSheet("QLineEdit { border-radius: 5px; }");
  search->setGeometry(width()/5, 4, width()/5*3, height()-4);

  addButton = new BeautifulUi::BeautifulButton(fa::fa_plus, this);
  addButton->setCheckable(false);
  connect(addButton, &BeautifulUi::BeautifulButton::clicked, this, &ToolBar::addGame);

  optionsButton->setGeometry(width()-optionsButton->width()-5, (height() - optionsButton->height())/2, optionsButton->width(), optionsButton->height());
  group->setGeometry(width()-group->width()-5-5-optionsButton->width(), (height() - group->height())/2, group->width(), group->height());
  setContentsMargins(5, 2, 5, 2);
}

void ToolBar::resizeEvent(QResizeEvent *event) {
  optionsButton->setGeometry(width()-optionsButton->width()-5, (height() - optionsButton->height())/2+1, optionsButton->width(), optionsButton->height());
  group->setGeometry(width()-group->width()-5-20-optionsButton->width(), (height() - group->height())/2+1, group->width(), group->height());
  addButton->setGeometry(5, (height() - addButton->height())/2+1, 30, addButton->height());
  search->setGeometry(width()/12*3, 6, width()/12*6, height()-9);
}