#include <vector>
#include <string>
#include <iostream>
#include "../main/bluise.h"
#include "../command_line/command_processor.h"

void qt_win() {}

int main(int argc, char** argv) {  
    bluise_core::readGLL();
    if(argc==1) {
        qt_win();
    }
    else {
        bluise_command_line::process_command_line(argc, argv);
    }

    return 0;
}