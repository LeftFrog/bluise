#include <QtWidgets>
#include "bluise.h"
#include "GameListModel.h"
#include "GameListView.h"

int qt_win(int argc, char** argv) {
    QApplication a(argc, argv);


    GameListModel model;
    GameListView w{&model};

    w.show();
    return a.exec();
}