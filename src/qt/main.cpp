#include <QtWidgets>
#include "bluise.h"
#include "GameListWidget.h"

int qt_win(int argc, char** argv) {
    QApplication a(argc, argv);
    GameListWidget w;
    w.setPalette(a.palette());
    w.show();
    return a.exec();
}