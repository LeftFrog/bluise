#include "bluise.h"
#include "invalid_path.h"
#include "GameListModel.h"
#include <iostream>
#include <QtWidgets>
#include "CoverDelegate.h"
#include "GameInfoWidget.h"

void qt_win() {
  GameListModel model;
  QListView view;
  view.setModel(&model);
  view.show();
}

int main(int argc, char **argv) {
  QApplication a(argc, argv);
  bluise_core::readGamesJSON();
  // if (argc == 1) {
    GameListModel model;
    QSplitter window(Qt::Vertical);
    QListView view;
    window.addWidget(&view);
    GameInfoWidget *info = new GameInfoWidget(&window);
    window.addWidget(info);
    info->hide();

    view.setViewMode(QListView::IconMode);
    view.setModel(&model);
    view.setItemDelegate(new CoverDelegate(QSize(265/1.5, 376/1.5)));
    view.setResizeMode(QListView::Adjust);
    view.setUniformItemSizes(true);
    view.setSizeAdjustPolicy(QListView::AdjustToContentsOnFirstShow);
    view.setWrapping(true);
    view.setSpacing(15);
    view.setFlow(QListView::LeftToRight);
    window.resize(800, 600);
    QObject::connect(&view, &QListView::clicked, info, &GameInfoWidget::setGame);
    window.show();
  // } else {
  //   command_processor::process_command_line(argc, argv);
  // }
  bluise_core::saveGamesJSON();
  return a.exec();
}
