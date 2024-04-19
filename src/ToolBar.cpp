#include "ToolBar.h"
#include <QPushButton>
#include <QMenu>
#include "BeautifulButton.h"
#include "BeautifulButtonGroup.h"
#include "QtAwesome/QtAwesome/QtAwesome.h"

ToolBar::ToolBar(QWidget *parent) : QWidget(parent) {
  // setMovable(false);
  // setFloatable(false);
  setFixedHeight(36);

  fa::QtAwesome *awesome = new fa::QtAwesome;
  awesome->initFontAwesome();

  QMenu *menu = new QMenu;
  menu->addAction("Lol");

  // BeautifulUi::BeautifulButton *settingsButton = new BeautifulUi::BeautifulButton(this);
  // settingsButton->setIcon(awesome->icon(fa::fa_solid, fa::fa_ellipsis));
  // settingsButton->setMenu(menu);

  QWidget *spacer = new QWidget;
  spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  BeautifulUi::BeautifulButtonGroup *group = new BeautifulUi::BeautifulButtonGroup(this);
  BeautifulUi::BeautifulButton *listView = new BeautifulUi::BeautifulButton(group);
  BeautifulUi::BeautifulButton *tableView = new BeautifulUi::BeautifulButton(group);
  tableView->setIcon(awesome->icon(fa::fa_styles::fa_solid, fa::fa_table_cells_large));
  listView->setIcon(awesome->icon(fa::fa_styles::fa_solid, fa::fa_list_ul));
  group->addButton(tableView);
  group->addButton(listView);
  QHBoxLayout *HBL = new QHBoxLayout;
  // HBL->addWidget(spacer);
  // HBL->addWidget(group);
  // HBL->addWidget(settingsButton);
  setContentsMargins(5, 2, 5, 2);
  // setLayout(HBL);


  // addWidget(spacer);
  // addWidget(wid);
  // addWidget(settingsButton);
}