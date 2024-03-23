#include "GameScrollArea.h"
#include "bluise.h"
#include "invalid_path.h"
#include <QApplication>
#include <iostream>

int qt_win(int argc, char **argv) {
  QApplication a(argc, argv);
  GameScrollArea w;
  w.show();
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
