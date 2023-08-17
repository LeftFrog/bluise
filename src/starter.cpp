#include "bluise.h"
#include "./command_line/command_processor.cpp"

int main(int argc, char** argv) {
    bluise_core::readGLL();
    if(argc > 0) {
        process_command_line(argc, argv);
    }
    bluise_core::saveGLL();
    return 0;
}