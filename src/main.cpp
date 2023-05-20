#include "command_processor.cpp"

int main(int argc, char** argv) {  

    readGLL();
    if(argc==1) {
        process_commands();
    }
    else {
        if(string(argv[1])=="--help" || string(argv[1])=="-h") {
            print_help_console();
        }
        else if(string(argv[1])=="--add" || string(argv[1])=="-a") {
            add_game();
        }
        else if(string(argv[1])=="--list" || string(argv[1])=="-l") {
            print_game_vector();
        }
        else {
            std::cout << "Unknown command, plese type \"bluise -h\" to show help! \n";
        }
    }

    return 0;
}