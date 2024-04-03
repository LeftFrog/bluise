#include "GameScrollArea.h"
#include "bluise.h"
#include "invalid_path.h"
#include <QApplication>
#include <QSplitter>
#include "Dock.h"
#include <iostream>

int qt_win(int argc, char **argv) {
  QApplication a(argc, argv);
  QSplitter splitter(Qt::Vertical);
  GameScrollArea *gameScrollArea = new GameScrollArea(&splitter);
  Dock *w = new Dock(&splitter);
  QObject::connect(w, &Dock::added, gameScrollArea, &GameScrollArea::added);
  QObject::connect(w, &Dock::sort, gameScrollArea, &GameScrollArea::sort);
  QObject::connect(w, &Dock::filter, gameScrollArea, &GameScrollArea::filter);
  splitter.resize(gameScrollArea->width(), 600);
  splitter.setHandleWidth(1);
  splitter.addWidget(w);
  splitter.addWidget(gameScrollArea);
  splitter.show();
  return a.exec();
}

int main(int argc, char **argv) {
  bluise_core::readGamesJSON();
  if (argc == 1) {
    qt_win(argc, argv);
  } else {
    command_processor::process_command_line(argc, argv);
  }
  bluise_core::saveGamesJSON();
  return 0;
}
