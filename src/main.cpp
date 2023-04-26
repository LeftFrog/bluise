#include <iostream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <filesystem>
#include "invalid_path.h"
#include "Game.h"

vector<Game> games{};
string splitter = "<------------------------------->";

void print_game_vector() {
    std::cout << splitter << endl;
    for(int i = 0; i < games.size(); ++i) {
        std::cout << i+1 << " | " << games[i].get_name() << endl;
    }
    std::cout << splitter << endl;
}

vector<Game>::iterator find_game(const string& name) {
    for(vector<Game>::iterator it = games.begin(); it != games.end(); ++it) {
        if(it->get_name() == name) {
            return it;
        }
    }
    return vector<Game>::iterator();
}

void add_game() {
    string name;
    string working_directory;
    string executable;
    string save_path;

    std::cin.ignore();
    std::cout << "Enter the name of the game: \n";

    std::getline(std::cin, name);
    if(!(find_game(name)==vector<Game>::iterator())) {
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
              <<    "exit - exit the program\n" \
              <<    splitter << endl;
}

void delete_game() {
    std::cout << "Enter the name of the game: \n";
    string name;
    std::cin.ignore();
    std::getline(std::cin, name);
    if(games.size()==1) {
        games.clear();
        std::cout << "The game successfully deleted.\n";
        return;
    }
    games.erase(find_game(name));
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
    std::cout << "Enter the name of the game or its id: \n";
    string input;
    cin.ignore();
    std::getline(std::cin, input);
    vector<Game>::iterator game = find_game(input);
    show_game_info(game);
}

void run_game() {
    std::cout << "Enter the name of the game or its id: \n";
    string name;
    std::cin.ignore();
    std::getline(std::cin, name);
    find_game(name)->execute();
    std::cout << "The game is running. \n";
}

void edit_game() {
    std::cout << "Enter the name of the game or its id: \n";
    string name;
    std::cin.ignore();
    std::getline(std::cin, name);
    vector<Game>::iterator game = find_game(name);
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
    string enter_command_prompt = "Enter command: \n";
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
            exit(0);
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
        else {
            std::cout << "Unknown command. Enter help to get list of the commands. \n";
        }
        std::cout << enter_command_prompt;
    }
}

int main(int argc, char** argv) {
    try {
        games.push_back(Game("Minecraft", "/home/leftfrog/.minecraft/", "/usr/bin/tlauncher", "/home/leftfrog/.minecraft/"));
    }
    catch (const invalid_path& err) {
        cerr << err.what();
    }
    
    process_commands();
    return 0;
}