#include "bluise.h"
#include "GameListModel.h"
#include <QtWidgets>

int qt_win(int argc, char** argv) {
    QApplication a(argc, argv);
    GameListModel model;
    QListView w;
    w.setWindowTitle("Bluise");
    w.setWindowIcon(QIcon(QString("/home/leftfrog/Documents/Bluise/icons/game.png")));
    w.setModel(&model);
    w.show();
    return a.exec();
}