#include <QtWidgets>
#include "bluise.h"
#include "GameWidget.h"

int qt_win(int argc, char** argv) {
    QApplication a(argc, argv);
    GameWidget w;
    w.setPalette(a.palette());
    w.show();
    return a.exec();
}