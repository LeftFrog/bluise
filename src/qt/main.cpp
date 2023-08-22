#include "bluise.h"
#include <QtWidgets>

int qt_win(int argc, char** argv) {
    QApplication a(argc, argv);
    QWidget w;
    QVBoxLayout* VBL = new QVBoxLayout();
    for(int i = 0; i < bluise_core::games.size(); ++i) {
        VBL->addWidget(new QLabel(bluise_core::games[i].get_name().c_str()));
    }
    w.setLayout(VBL);
    w.show();
    return a.exec();
}