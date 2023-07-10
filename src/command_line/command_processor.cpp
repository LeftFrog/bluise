#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <filesystem>
#include "../main/bluise.h"

namespace fs = std::filesystem;
const string HOME = getenv("HOME");

string splitter = "<------------------------------->";

inline string get_game_var(const string& var_name) {
    std::cout << "Enter a "+var_name+" of a game: \n";
    string var;
    std::getline(std::cin, var);
    return var;
}

void print_game_vector() {
    std::cout << splitter << endl;
    for(int i = 0; i < games.size(); ++i) {
        std::cout << i+1 << " | " << games[i].get_name() << endl;
    }
    std::cout << splitter << endl;
}

void back(const string& name) {
    auto game = find(games.begin(), games.end(), name);

    if(game==games.end()) {
        std::cout << "There isn't this game!\n";
        return;
    }

    string back_path = HOME+"/Documents/Bluise/backs/"+name+"/";
    if(!fs::exists(back_path)) {
        if(!fs::create_directory(back_path)) {
            std::cout << "Can't create directory!\n";
            return;
        }
    }
    std::system(string("cp -R \""+game->get_save_path()+".\" \""+back_path+"\"").c_str());
    std::cout << "Successfully made backup of your saves.\n";
}

void recover(const string& name) {
    auto game = find(games.begin(), games.end(), name);

    if((game==games.end())) {
        std::cout << "There isn't this game!\n";
        return;
    }

    string back_path = HOME+"/Documents/Bluise/backs/"+name+"/";
    if(!fs::exists(back_path)) {
        std::cout << "There isn't backups of saves of your game\n!";
    }
    std::system(string("cp -R \""+back_path+".\" \""+game->get_save_path()+"\"").c_str());
    std::cout << "Successfully recovered your saves.\n";
}

void add_game() {
    string name = get_game_var("name");

    if(!(find(games.begin(), games.end(), name)==games.end())) {
        std::cout << "There is a game with the same name!\n";
        return;
    }

    string working_directory = get_game_var("working_directory");
    string executable = get_game_var("executable");
    string save_path = get_game_var("save_path");

    try {
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
              <<    "--help or -h - shows this list of the commands\n" \
              <<    "--list or -l - shows the list of games\n" \
              <<    "--add or -a - adds a game to the list\n" \
              <<    "--run or -r {name of a game} - runs game\n" \
              <<    "--back or -b {name of a game} - makes backup of your saves\n" \
              <<    "--recover or -R {name of a game} - recover syour saves\n" \
              <<    "--show-info or -s {name of a game} - shows info about a game\n" \
              <<    "--delete or -d {name of a game} - deletes game from list\n" \
              <<    "--edit or -e {name of a game} - edits your game\n" \
              <<    splitter << endl;
}

void delete_game(const string& name) {
    auto game = find(games.begin(), games.end(), name);
    if(game==games.end()) {
        std::cout << "There isn't this game\n";
        return;
    }
    std::cout << "Are you sure that you want delete " + game->get_name() + "? (y/n): ";
    char answer;
    std::cin >> answer;
    if(!(answer=='y')) {
        return;
    }
    std::cout << endl;  

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

void show_info(const string& name) {
    auto game = find(games.begin(), games.end(), name);
    if(game==games.end()) {
        std::cout << "There isn't this game\n";
        return;
    }
    show_game_info(game);
}

void run_game(const string& name) {
    auto game = find(games.begin(), games.end(), name);
    if(game==games.end()) {
        std::cout << "There isn't this game\n";
        return;
    }
    game->execute();
    std::cout << "The game is running. \n";
}

inline bool sure_change(const string& var, const string& val) {
    std::cout << "Are you sure that you want change " + var + " to " + val + "? (y/n): ";
    char answer;
    std::cin >> answer;
    return answer=='y' ? true : false; 
}

void edit_game(string name) {
    vector<Game>::iterator game = find(games.begin(), games.end(), name);
    if(game==games.end()) {
        std::cout << "There isn't this game\n";
        return;
    }

    show_game_info(game);

    std::cout   << "Choose option to edit(name, working_directory, executable, save_path): \n";
    string var;
    std::cin >> var;
    std::cin.ignore();
    string val;

    try {
        if(var=="name") {
            val = get_game_var(var);
            sure_change(var, val);    
            game->set_name(val);
        }
        else if(var=="working_directory") {
            val = get_game_var(var);
            sure_change(var, val); 
            game->set_working_directory(val);
        }
        else if(var=="executable") {
            val = get_game_var(var);
            sure_change(var, val); 
            game->set_executable(val);
        }
        else if(var=="save_path") {
            val = get_game_var(var);
            sure_change(var, val); 
            game->set_save_path(val);
        }
        else {
            std::cout << "Unknown variable!\n";
            return;
        }
    }
    catch (const invalid_path& err) {
        cerr << err.what();
    }
}


void process_command_line(int& argc, char** argv) {
    if(string(argv[1])=="--help" || string(argv[1])=="-h") {
        print_help_console();
    }
    else if(string(argv[1])=="--add" || string(argv[1])=="-a") {
        add_game();
    }
    else if(string(argv[1])=="--list" || string(argv[1])=="-l") {
        print_game_vector();
    }
    else if((string(argv[1])=="--run" || string(argv[1])=="-r") && argc == 3) {
        run_game(string(argv[2]));
    }
    else if((string(argv[1])=="--back" || string(argv[1])=="-b") && argc == 3) {
        back(string(argv[2]));
    }
    else if((string(argv[1])=="--recover" || string(argv[1])=="-R") && argc == 3) {
        recover(string(argv[2]));
    }
    else if((string(argv[1])=="--show-info" || string(argv[1])=="-s") && argc == 3) {
        show_info(string(argv[2]));
    }
    else if((string(argv[1])=="--delete" || string(argv[1])=="-d") && argc == 3) {
        delete_game(string(argv[2]));
    }
    else if((string(argv[1])=="--edit" || string(argv[1])=="-e") && argc == 3) {
        edit_game(string(argv[2]));
    }
    else {
        std::cout << "Unknown command, plese type \"bluise -h\" to show help! \n";
    }
    saveGLL();
}