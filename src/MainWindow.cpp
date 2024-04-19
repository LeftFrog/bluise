#include "MainWindow.h"
#include "GameListModel.h"
#include "GameInfoWidget.h"
#include "CoverDelegate.h"
#include <QSplitter>
#include <QListView>
#include <QTableView>
#include <QStringListModel>
#include <QMenuBar>
#include "GameAddWidget.h"
#include "bluise.h"
#include <QToolBar>
#include <QDockWidget>
#include "ToolBar.h"
#include "GameProxyModel.h"
#include "BeautifulButton.h"
#include "QtAwesome/QtAwesome/QtAwesome.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setUnifiedTitleAndToolBarOnMac(true);
  // setWindowTitle("Bluise");
  resize(1900, 800);

  menuBar = new QMenuBar();
  QMenu *file = menuBar->addMenu("&File");
  file->addAction("New Game");
  connect(file, &QMenu::triggered, this, &MainWindow::addGame);
  setMenuBar(menuBar);

  QSplitter *splitter = new QSplitter(Qt::Vertical, this);

  fa::QtAwesome *awesome = new fa::QtAwesome(this);
  awesome->initFontAwesome();

  ToolBar *toolbar = new ToolBar(this);
  QMenu *menu = new QMenu;
  menu->addAction("Lol");
  BeautifulUi::BeautifulButton *settingsButton = new BeautifulUi::BeautifulButton(this);
  settingsButton->setIcon(awesome->icon(fa::fa_solid, fa::fa_ellipsis));
  settingsButton->setMenu(menu);
  QWidget *spacer = new QWidget;
  spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  toolbar->addWidget(spacer);
  toolbar->addWidget(settingsButton);
  addToolBar(Qt::TopToolBarArea, toolbar);

  list = new QListView(splitter);
  splitter->addWidget(list);
  GameInfoWidget *info = new GameInfoWidget(splitter);
  splitter->addWidget(info);
  // list->setModel(&model);
  info->hide();
  splitter->setHandleWidth(2);
  splitter->setCollapsible(1, false);

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

  connect(list, &QListView::clicked, info, &GameInfoWidget::setGame);

  setCentralWidget(splitter);
}

MainWindow::~MainWindow() {
  bluise_core::saveGamesJSON();
}
void MainWindow::addGame(QAction* action) {
  if(action->text() == "New Game") {
    GameAddWidget *add_widget = new GameAddWidget;
    connect(add_widget, SIGNAL(added()), list, SLOT(update()));
    add_widget->show();
  }
}