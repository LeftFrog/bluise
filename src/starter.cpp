#include <QtWidgets>
#include "MainWindow.h"

int main(int argc, char **argv) {
  QApplication a(argc, argv);
  a.setWindowIcon(QIcon("/Users/leftfrog/Projects/bluise/res/1024-mac-1024.png"));
  MainWindow w;
  w.show();
  return a.exec();
}
