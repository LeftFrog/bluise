#include "ToolBar.h"
#include <QPushButton>
#include <QMenu>
#include "QtAwesome/QtAwesome/QtAwesome.h"
#include <QActionGroup>

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

  sortButton = new BeautifulUi::BeautifulButton(fa::fa_sort, this);
  QMenu *sortMenu = new QMenu();
  QActionGroup *sortGroup = new QActionGroup(sortMenu);
  QAction *nameSort = new QAction("Name");
  nameSort->setCheckable(true);
  nameSort->setChecked(true);
  sortMenu->addAction(nameSort);
  sortGroup->addAction(nameSort);
  QAction *yearSort = new QAction("Release year");
  yearSort->setCheckable(true);
  sortMenu->addAction(yearSort);
  sortGroup->addAction(yearSort);
  sortGroup->setExclusive(true);
  sortButton->setMenu(sortMenu);
  connect(sortMenu, &QMenu::triggered, this, &ToolBar::sort);

  search = new QLineEdit(this);
  search->setStyleSheet("QLineEdit { border-radius: 5px; }");
  search->setGeometry(width()/5, 4, width()/5*3, height()-4);
  search->setPlaceholderText("Search game by name");

  addButton = new BeautifulUi::BeautifulButton(fa::fa_plus, this);
  addButton->setCheckable(false);
  connect(addButton, &BeautifulUi::BeautifulButton::clicked, this, &ToolBar::addGame);

  setContentsMargins(10, 6, 6, 10);
}

void ToolBar::resizeEvent(QResizeEvent *event) {
  optionsButton->setGeometry(width()-optionsButton->width()-contentsMargins().right(), (height() - optionsButton->height())/2+1, optionsButton->width(), optionsButton->height());
  sortButton->setGeometry(width()-sortButton->width()-contentsMargins().right()*2-optionsButton->width(), (height() - sortButton->height())/2+1, sortButton->width(), sortButton->height());
  group->setGeometry(sortButton->x()-15-group->width(), (height() - group->height())/2+1, group->width(), group->height());
  addButton->setGeometry(contentsMargins().left(), (height() - addButton->height())/2+1, 30, addButton->height());
  search->setGeometry(width()/12*3, contentsMargins().top(), width()/12*6, height()-9);
}

void ToolBar::sort(QAction *action) {
  if(action->text()=="Release year") {
    emit setSort(Qt::UserRole+2);
  } else if(action->text()=="Name") {
    emit setSort(Qt::DisplayRole);
  }
}