#include "bluise.h"
#include "GameWidget.h"
#include "invalid_path.h"
#include <iostream>
#include <QApplication>
#include <QGridLayout>



int qt_win(int argc, char** argv) {
    QApplication a(argc, argv);
    QWidget w;
    Game* g = &bluise_core::games[0];
    QGridLayout* Grid = new QGridLayout();
    for(int i = 0; i < bluise_core::games.size(); ++i) {
        Grid->addWidget(new GameWidget(&bluise_core::games[i], &w), 1, i);
    }
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
