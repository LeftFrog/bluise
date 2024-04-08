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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setUnifiedTitleAndToolBarOnMac(true);
  // setWindowTitle("Bluise");
  resize(973, 600);

  menuBar = new QMenuBar();
  QMenu *file = menuBar->addMenu("&File");
  file->addAction("New Game");
  connect(file, &QMenu::triggered, this, &MainWindow::addGame);
  setMenuBar(menuBar);

  QSplitter *splitter = new QSplitter(Qt::Vertical, this);
  ToolBar *toolbar = new ToolBar(splitter);
  splitter->addWidget(toolbar);
  list = new QListView(splitter);
  splitter->addWidget(list);
  GameInfoWidget *info = new GameInfoWidget(splitter);
  splitter->addWidget(info);
  list->setModel(&model);
  info->hide();
  splitter->setHandleWidth(2);

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