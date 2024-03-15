#include "bluise.h"
#include "GameWidget.h"
#include "invalid_path.h"
#include <iostream>
#include <QApplication>
#include <QGridLayout>
#include "GameListWidget.h"



int qt_win(int argc, char** argv) {
    QApplication a(argc, argv);
    GameListWidget w;
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
