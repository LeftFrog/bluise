#include <QtWidgets>
#include "bluise.h"
#include "GameListModel.h"

int qt_win(int argc, char** argv) {
    QApplication a(argc, argv);
    QTabWidget tab;

    GameListModel model;
    QListView* w = new QListView();
    QObject::connect(w, &QListView::doubleClicked, &model, &GameListModel::run_game);

    tab.setTabPosition(QTabWidget::West);

    tab.addTab(w, "Games");
    tab.setWindowTitle("Bluise");
    tab.setWindowIcon(QIcon(QString("/home/leftfrog/Documents/Bluise/icons/game.png")));
    w->setModel(&model);
    w->setViewMode(QListView::IconMode);
    w->setMovement(QListView::Snap);
    w->setGridSize(QSize(70, 70));
    tab.show();
    return a.exec();
}