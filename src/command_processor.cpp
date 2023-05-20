#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <filesystem>
#include "invalid_path.h"
#include "gll_syntax_error.h"
#include "Game.h"
#include "GLLReader.cpp"

namespace fs = std::filesystem;
const string HOME = getenv("HOME");

vector<Game> games{};
string splitter = "<------------------------------->";

inline void saveGLL() {
    sort(games.begin(), games.end());
    ofstream oft(HOME+"/Documents/ReWdten/Games.gll", std::ofstream::trunc);
    oft << games;
    oft.close();
}

inline void readGLL() {

    ifstream ist(HOME+"/Documents/Redten/Games.gll");
    try {
        ist >> games;
    }
    catch (const invalid_path& err) {
        cerr << err.what();
    }
    catch (const gll_syntax_error& err) {
        cerr << err.what();
    }
 
    ist.close();
}

void print_game_vector() {
    std::cout << splitter << endl;
    for(int i = 0; i < games.size(); ++i) {
        std::cout << i+1 << " | " << games[i].get_name() << endl;
    }
    std::cout << splitter << endl;
}

void back() {
    string name;
    std::cin.ignore();
    std::cout << "Enter a name of a game: \n";
    std::getline(std::cin, name);

    auto game = find(games.begin(), games.end(), name);

    if(game==vector<Game>::iterator()) {
        std::cout << "There isn't this game!\n";
        return;
    }

    string back_path = HOME+"/Documents/Redten/backs/"+name+"/";
    if(!fs::exists(back_path)) {
        if(!fs::create_directory(back_path)) {
            std::cout << "Can't create directory!\n";
            return;
        }
    }
    std::system(string("cp -R "+game->get_save_path()+" "+back_path).c_str());
    std::cout << "Successfully made backup of your saves.\n";
}

void recover() {
    string name;
    std::cin.ignore();
    std::cout << "Enter a name of a game: \n";
    std::getline(std::cin, name);

    auto game = find(games.begin(), games.end(), name);

    if(game==vector<Game>::iterator()) {
        std::cout << "There isn't this game!\n";
        return;
    }

    string back_path = HOME+"/Documents/Redten/backs/"+name+"/";
    if(!fs::exists(back_path)) {
        std::cout << "There isn't backups of saves of your game\n!";
    }
    std::system(string("cp -R "+back_path+" "+game->get_save_path()).c_str());
    std::cout << "Successfully recovered your saves.\n";
}

void add_game() {
    string name;
    string working_directory;
    string executable;
    string save_path;

    std::cin.ignore();
    std::cout << "Enter a name of a game: \n";

    std::getline(std::cin, name);
    if(!(find(games.begin(), games.end(), name)==vector<Game>::iterator())) {
        std::cout << "There is a game with the same name!\n";
        return;
    }
    try {
        std::cout << "Enter the working directory of the game: \n";
        std::getline(std::cin, working_directory);
        std::cout << "Enter the path to the executable of the game: \n";
        std::getline(std::cin, executable);
        std::cout << "Enter the save path of the game: \n";
        std::getline(std::cin, save_path);
        games.push_back(Game(name, working_directory, executable, save_path));
        std::cout << "The game successfully added.\n";
    }
    catch(const invalid_path& err) {
        cerr << err.what() << endl;
    }
}

void print_help_console() {
    std::cout <<    splitter \
              <<    "\nCommands: \n" \
              <<    "help - shows this list of the commands\n" \
              <<    splitter << endl;
}

void print_help() {
    std::cout <<    splitter \
              <<    "\nCommands: \n" \
              <<    "add - add a game to the data base\n"  \
              <<    "list - print names of all games\n" \
              <<    "delete - delete a game from db\n" \
              <<    "help - print list of commands\n" \
              <<    "run - run a game\n" \
              <<    "edit - edit exist game\n" \
              <<    "show_info - shows info about a game\n" \
              <<    "save - saves your games list to file\n" \
              <<    "load - loads your games list from file\n" \
              <<    "back - makes backup of saves of your game\n" \
              <<    "exit - exit the program\n" \
              <<    splitter << endl;
}

void delete_game() {
    std::cout << "Enter a name of a game: \n";
    string name;
    std::cin.ignore();
    std::getline(std::cin, name);
    auto game = find(games.begin(), games.end(), name);
    if(game==vector<Game>::iterator()) {
        std::cout << "Incorrect name of a game\n";
        return;
    }
    if(games.size()==1) {
        games.clear();
        std::cout << "The game successfully deleted.\n";
        return;
    }
    games.erase(game);

    std::cout << "The game successfully deleted.\n";
}

void show_game_info(const vector<Game>::iterator& game) {
    std::cout   << splitter << endl << "Name: " + game->get_name()  << endl \
                << "Working directory: " + game->get_working_directory()  << endl\
                << "Executable: " + game->get_executable() << endl \
                << "Save path: " + game->get_save_path() << endl \
                << splitter << endl;
}

void show_info() {
    std::cout << "Enter a name of a game: \n";
    string input;
    cin.ignore();
    std::getline(std::cin, input);
    auto game = find(games.begin(), games.end(), input);
    if(game==vector<Game>::iterator()) {
        std::cout << "Incorrect name of a game\n";
        return;
    }
    show_game_info(game);
}

void run_game() {
    std::cout << "Enter a name of a game: \n";
    string name;
    std::cin.ignore();
    std::getline(std::cin, name);
    auto game = find(games.begin(), games.end(), name);
    if(game==vector<Game>::iterator()) {
        std::cout << "Incorrect name of a game\n";
        return;
    }
    game->execute();
    std::cout << "The game is running. \n";
}

void edit_game() {
    std::cout << "Enter a name of a game: \n";
    string name;
    std::cin.ignore();
    std::getline(std::cin, name);
    vector<Game>::iterator game = find(games.begin(), games.end(), name);
    if(game==vector<Game>::iterator()) {
        std::cout << "Incorrect name of a game\n";
        return;
    }

    show_game_info(game);

    std::cout   << "Choose option to edit(name, working_directory, executable, save_path): \n";
    string var;
    std::cin >> var;
    std::cout << "Enter value of the variable: \n";

    try {
        if(var=="name") {
            std::cin.ignore();
            string name;
            std::getline(std::cin, name);
            game->set_name(name);
        }
        else if(var=="working_directory") {
            std::cin.ignore();
            string working_directory;
            std::getline(std::cin, working_directory);
            game->set_working_directory(working_directory);
        }
        else if(var=="executable") {
            std::cin.ignore();
            string executable;
            std::getline(std::cin, executable);
            game->set_executable(executable);
        }
        else if(var=="save_path") {
            std::cin.ignore();
            string save_path;
            std::getline(std::cin, save_path);
            game->set_save_path(save_path);
        }
    }
    catch (const invalid_path& err) {
        cerr << err.what();
    }
}

void process_commands() {
    string enter_command_prompt = "Enter a command: \n";
    string command;
    std::cout << enter_command_prompt;
    while(std::cin>>command) {
        std::transform(command.begin(), command.end(), command.begin(), [](unsigned char c){ return std::tolower(c); });
        if(command=="add") {
            add_game();
        }
        else if(command=="list") {
            print_game_vector();
        }
        else if(command=="help") {
            print_help();
        }
        else if(command=="delete") {
            delete_game();
        }
        else if(command=="exit") {
            return;
        }
        else if(command=="run") {
            run_game();
        }
        else if(command=="show_info") {
            show_info();
        }
        else if(command=="edit") {
            edit_game();
        }
        else if(command=="load") {
            readGLL();
        }
        else if(command=="save") {
            saveGLL();
        }
        else if(command=="sync") {
            std::cout << "Now this func is not available, but you can use syncthing to sync your saves!\n";
        }
        else if(command=="back") {
            back();
        }
        else if(command=="recover") {
            recover();
        }
        else {
            std::cout << "Unknown command. Enter help to get list of the commands. \n";
        }
        std::cout << enter_command_prompt;
    }
}