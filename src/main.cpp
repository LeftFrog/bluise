#include "ncurses_ui.cpp"

int main(int argc, char** argv) {  

    readGLL();
    if(argc==1) {
        print_ui();
    }
    else {
        process_command_line(argc, argv);
    }

    return 0;
}