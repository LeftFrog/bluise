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
  // w->resize(gameScrollArea->width(), 50);
  // w->rootObject()->setProperty("width", gameScrollArea->width());
  // w->rootObject()->setProperty("height", 50);
  splitter.resize(1280, 600);
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
