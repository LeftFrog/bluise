#include "bluise.h"
#include "GameListModel.h"
#include <QtWidgets>

int qt_win(int argc, char** argv) {
    QApplication a(argc, argv);
    GameListModel model;
    QListView w;
    QObject::connect(&w, &QListView::doubleClicked, &model, &GameListModel::run_game);
    w.setWindowTitle("Bluise");
    w.setWindowIcon(QIcon(QString("/home/leftfrog/Documents/Bluise/icons/game.png")));
    w.setModel(&model);
    w.show();
    return a.exec();
}