#include "MainWindow.h"
#include "./ModelView/GameListModel.h"
#include "./Widgets/GameInfoWidget.h"
#include "./ModelView/CoverDelegate.h"
#include <QSplitter>
#include <QListView>
#include <QTableView>
#include <QStringListModel>
#include <QMenuBar>
#include "./Widgets/AddLocalInstalledGameWidget.h"
#include "./BluiseCore/bluise.h"
#include <QToolBar>
#include <QDockWidget>
#include "./Widgets/ToolBar.h"
#include "./ModelView/GameProxyModel.h"
#include "./BeautifulUI/BeautifulButton.h"
#include "QtAwesome/QtAwesome/QtAwesome.h"
#include <QToolButton>
#include "Widgets/AddGameWidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  bluise_core::readGamesJSON();
  setUnifiedTitleAndToolBarOnMac(true);
  // setWindowTitle("Bluise");
  resize(1900, 800);

  menuBar = new QMenuBar();
  QMenu *file = menuBar->addMenu("&File");
  file->addAction("New Game");
  connect(file, &QMenu::triggered, this, &MainWindow::handleMenus);
  setMenuBar(menuBar);

  QSplitter *splitter = new QSplitter(Qt::Vertical, this);

  fa::QtAwesome *awesome = new fa::QtAwesome(this);
  awesome->initFontAwesome();

  ToolBar *toolbar = new ToolBar(this);
  //addToolBar(Qt::TopToolBarArea, toolbar);
  connect(toolbar, &ToolBar::addGame, this, &MainWindow::addGame);
  splitter->addWidget(toolbar);
  splitter->setCollapsible(0, false);

  list = new QListView(splitter);
  splitter->addWidget(list);
  GameInfoWidget *info = new GameInfoWidget(splitter);
  splitter->addWidget(info);
  // list->setModel(&model);
  info->hide();
  splitter->setHandleWidth(2);
  splitter->setCollapsible(2, false);

  GameProxyModel *proxy = new GameProxyModel(this);
  proxy->setSourceModel(&model);
  list->setModel(proxy);
  proxy->sort(0, Qt::AscendingOrder);
  list->setViewMode(QListView::IconMode);
  list->setItemDelegate(new CoverDelegate(QSize(265/1.5, 376/1.5)));
  list->setResizeMode(QListView::Adjust);
  list->setUniformItemSizes(true);
  list->setSizeAdjustPolicy(QListView::AdjustToContentsOnFirstShow);
  list->setWrapping(true);
  list->setSpacing(15);
  list->setFlow(QListView::LeftToRight);

  proxy->setFilterRole(Qt::UserRole + 3);
  connect(toolbar, &ToolBar::setFilter, proxy, &GameProxyModel::setFilterExp);
  connect(toolbar, &ToolBar::setName, proxy, &GameProxyModel::setNameExp);
  connect(info, &GameInfoWidget::removeSignal, &model, &GameListModel::removeGame);

  connect(list, &QListView::clicked, info, &GameInfoWidget::setGame);
  connect(toolbar, &ToolBar::setSort, proxy, &QSortFilterProxyModel::setSortRole);

  setWindowIcon(QIcon("/Users/leftfrog/Projects/bluise/res/1024-mac.png"));

  setCentralWidget(splitter);
}

MainWindow::~MainWindow() {
  bluise_core::saveGamesJSON();
}

void MainWindow::handleMenus(QAction* action) {
  if(action->text() == "New Game") {
    addGame();
  }
}

void MainWindow::addGame() {
  AddGameWidget* add_widget = new AddGameWidget();
  // AddLocalInstalledGameWidget *add_widget = new AddLocalInstalledGameWidget;
  // connect(add_widget, SIGNAL(added()), &model, SLOT(updateList()));
  add_widget->show();
}