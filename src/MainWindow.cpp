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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setUnifiedTitleAndToolBarOnMac(true);
  // setWindowTitle("Bluise");
  resize(973, 600);

  menuBar = new QMenuBar();
  QMenu *file = menuBar->addMenu("&File");
  file->addAction("New Game");
  connect(file, &QMenu::triggered, this, &MainWindow::addGame);
  setMenuBar(menuBar);

  toolBar = new QToolBar();
  toolBar->addAction("New Game");
  addToolBar(toolBar);
  toolBar->setMovable(false);

  QSplitter *splitter = new QSplitter(Qt::Vertical, this);
  list = new QListView(splitter);
  splitter->addWidget(list);
  GameInfoWidget *info = new GameInfoWidget(splitter);
  splitter->addWidget(info);
  list->setModel(&model);
  info->hide();

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
    add_widget->show();
  }
}