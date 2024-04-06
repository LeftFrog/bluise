#include "MainWindow.h"
#include "GameListModel.h"
#include "GameInfoWidget.h"
#include "CoverDelegate.h"
#include <QSplitter>
#include <QListView>
#include <QTableView>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("Bluise");
  resize(800, 600);
  QSplitter *splitter = new QSplitter(Qt::Vertical);
  list = new QListView();
  splitter->addWidget(list);
  GameInfoWidget *info = new GameInfoWidget;
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