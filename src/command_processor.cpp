#include "Game.h"
#include <vector>
#include <iostream>

vector<Game> games{Game("s", "s", "f", "L")};
string splitter = "<------------------------------->";

void print_game_vector() {
    std::cout << splitter << endl;
    for(int i = 0; i < games.size(); ++i) {
        std::cout << games[i].name << endl;
    }
    std::cout << splitter << endl;
}

void add_game() {
    string name;
    string working_directory;
    string executable;
    string save_path;
    std::cout << "Enter the name of the game: \n";
    std::cin >> name;
    std::cout << "Enter the working directory of the game: \n";
    std::cin >> working_directory;
    std::cout << "Enter the path to the executable of the game: \n";
    std::cin >> executable;
    std::cout << "Enter the save path of the game: \n";
    std::cin >> save_path;
    games.push_back(Game(name, working_directory, executable, save_path));
}

void print_help() {
    std::cout <<    splitter \
              <<    "\nCommands: \n" \
              <<    "add - add game to the command base\n"  \
              <<    "list - print names of all games\n" \
              <<    splitter << endl;
}

void process_commands() {
    string enter_command_prompt = "Enter command: \n";
    string command;
    std::cout << enter_command_prompt;
    while(std::cin>>command) {
        if(command=="add") {
            add_game();
        }
        else if(command=="list") {
            print_game_vector();
        }
        else if(command=="help") {
            print_help();
        }
        std::cout << enter_command_prompt;
    }
}