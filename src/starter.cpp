#include "bluise.h"
#include "GameWidget.h"
#include "invalid_path.h"
#include <iostream>
#include <QApplication>
#include "GameListWidget.h"


int qt_win(int argc, char** argv) {
    QApplication a(argc, argv);
    QScrollArea w;
    GameListWidget* gameListWidget = new GameListWidget(&w);
    w.setWidget(gameListWidget);
    w.horizontalScrollBar()->setEnabled(false);
    w.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    w.verticalScrollBar()->setEnabled(true);
    w.resize(1280, 720);
    w.setAlignment(Qt::AlignHCenter);
    w.setMinimumWidth(gameListWidget->sizeHint().width());
    w.show();
    return a.exec();
}

int main(int argc, char** argv)
{
    bluise_core::readGLL();
    if (argc == 1) {
       qt_win(argc, argv);
    }
    else {
        command_processor::process_command_line(argc, argv);
    }
    bluise_core::saveGLL();
    return 0;
}
