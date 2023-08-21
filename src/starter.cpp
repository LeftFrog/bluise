#include "./command_line/command_processor.cpp"
#include "./command_line_ui/ncurses_ui.cpp"

int main(int argc, char** argv) {
    bluise_core::readGLL();
    if(argc == 1) {
        print_ui();
    }
    else {
        process_command_line(argc, argv);
    }
    bluise_core::saveGLL();
    return 0;
}