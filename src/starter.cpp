#include "./command_line/command_processor.cpp"
#include "./qt/main.cpp"

int main(int argc, char** argv) {
    bluise_core::readGLL();
    if(argc == 1) {
        qt_win(argc, argv);
    }
    else {
        process_command_line(argc, argv);
    }
    bluise_core::saveGLL();
    return 0;
}