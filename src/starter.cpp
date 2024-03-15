#include "bluise.h"
#include "GameWidget.h"
#include "invalid_path.h"
#include <iostream>
#include <QApplication>
#include <QGridLayout>

int qt_win(int argc, char** argv) {
    QApplication a(argc, argv);
    Game* g = &bluise_core::games[0];
    QWidget w;
    GameWidget* gamew = new GameWidget(g, &w);
    GameWidget* gamew2 = new GameWidget(++g, &w);
    QGridLayout* Grid = new QGridLayout();
    Grid->addWidget(gamew, 1, 1);
    Grid->addWidget(gamew2, 1, 2);
    w.setLayout(Grid);
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
