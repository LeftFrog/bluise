#include "command_processor.cpp"

int main(int argc, char** argv) {  

    readGLL();
    if(argc==1) {
        process_commands();
    }
    else {
        process_command_line(&argc, argv);
    }

    return 0;
}