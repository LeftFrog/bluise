#include <iostream>
#include "Game.h"
#include <vector>
#include <filesystem>
#include "invalid_path.h"

vector<Game> games{Game("Minecraft", "/home/leftfrog/.minecraft", "/usr/bin/tlauncher", "/home/leftfrog/.minecraft/saves")};
string splitter = "<------------------------------->";

void print_game_vector() {
    std::cout << splitter << endl;
    for(int i = 0; i < games.size(); ++i) {
        std::cout << i+1 << " | " << games[i].name << endl;
    }
    std::cout << splitter << endl;
}

vector<Game>::iterator find_game(const string& name) {
    for(vector<Game>::iterator it = games.begin(); it != games.end(); ++it) {
        if(it->name == name) {
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
    try {
        std::cout << "Enter the working directory of the game: \n";
        std::getline(std::cin, working_directory);
        if(!std::filesystem::exists(working_directory))
            throw invalid_path("Invalid working directory!");
        std::cout << "Enter the path to the executable of the game: \n";
        std::getline(std::cin, executable);
        if(!std::filesystem::exists(executable))
            throw invalid_path("Invalid executable!");
        std::cout << "Enter the save path of the game: \n";
        std::getline(std::cin, save_path);
        if(!std::filesystem::exists(save_path))
            throw invalid_path("Invalid save path!");
        games.push_back(Game(name, working_directory, executable, save_path));
        std::cout << "The game successfully added.\n";
    }
    catch(invalid_path& err) {
        cerr << err.what() << endl;
    }
}

void print_help() {
    std::cout <<    splitter \
              <<    "\nCommands: \n" \
              <<    "add - add a game to the data base\n"  \
              <<    "list - print names of all games\n" \
              <<    "delete - delete a game from db\n " \
              <<    "help - print list of commands\n" \
              <<    "run - run a game\n" \
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

void run_game() {
    std::cout << "Enter the name of the game: ";
    string name;
    std::cin >> name;
    string exec = find_game(name)->executable;
    std::string command = "nohup "+ exec + " &";
    std::system(command.c_str());
    std::cout << "The game is running. \n";
}

void show_game_info() {
    std::cout << "Enter the name of the game or its id: ";
    string input;
    std::cin >> input;
    vector<Game>::iterator game = find_game(input);
    std::cout   << splitter << endl << "Name: " + game->name  << endl \
                << "Working directory: " + game->working_directory  << endl\
                << "Executable: " + game->executable << endl \
                << "Save path: " + game->save_path << endl \
                << splitter << endl;
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
            show_game_info();
        }
        else {
            std::cout << "Unknown command. Enter help to get list of the commands. \n";
        }
        std::cout << enter_command_prompt;
    }
}

int main(int argc, char** argv) {
    process_commands();
    return 0;
}