#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <map>
#include "../main/bluise.h"

using bluise_core::games;
map<string, string> aliases;

string splitter = "<------------------------------->";

ostream& operator<<(ostream& os, map<string, string>& al) {
    for(auto pair : al) {
        os << pair.first << " = " << pair.second << '\n';
    }
        return os;
}

istream& operator>>(istream& is, map<string, string>& al) {
    string line;
    while(!is.eof()) {
        getline(is, line);
        int pos = line.find('=');
        if(pos==string::npos) {
            return is;
        }
        al[line.substr(0, pos-1)] = line.substr(pos+2, line.length()-1);
    }
    return is;
}

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
    try {
        bluise_core::back(name);
        std::cout << "Successfully made backup of your saves.\n";
    } catch(const bluise_error& err) {
        cerr << err.what() << endl;
    }
}

void recover(const string& name) {
    try {
        bluise_core::recover(name);
        std::cout << "Successfully recovered your saves.\n";
    } catch(const bluise_error& err) {
        cerr << err.what() << endl;
    }
}

void add_game() {
    string name = get_game_var("name");
    string working_directory = get_game_var("working_directory");
    string executable = get_game_var("executable");
    string save_path = get_game_var("save_path");

    try {
        bluise_core::add(name, working_directory, executable, save_path);
        std::cout << "The game successfully added.\n";
    }
    catch(const bluise_error& err) {
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
    std::cout << "Are you sure that you want delete " + name + "? (y/n): ";
    char answer;
    std::cin >> answer;
    if(!(answer=='y')) {
        return;
    }
    std::cout << endl;  
    try {
        bluise_core::delete_game(name);
        std::cout << "The game successfully deleted.\n";
    }
    catch(const bluise_error& err) {
        cerr << err.what() << endl;
    }
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
    try {
    bluise_core::run(name);
    std::cout << "Successfully ran the game.\n";
    } catch(const bluise_error& err) {
        cerr << err.what() << endl;
    }
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
    string val = get_game_var(var);

    try {
        bluise_core::edit(var, val, name);
    }
    catch (const bluise_error& err) {
        cerr << err.what();
    }
}

void create_alias(const string& name, const string& alias) {
    aliases[alias] = name;
    ofstream oft(bluise_core::HOME+"/Documents/Bluise/aliases.txt", std::ofstream::trunc);
    oft << aliases;
}

const string alias_of(const string& alias) {
    ifstream ist(bluise_core::HOME+"/Documents/Bluise/aliases.txt");
    ist >> aliases;
    string name;
    try {
    name = aliases.at(alias);
    } catch(out_of_range error) {
        return alias;
    }
    return name;
}

void delete_alias(const string& alias) {
    aliases.erase(alias);
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
        run_game(alias_of(string(argv[2])));
    }
    else if((string(argv[1])=="--back" || string(argv[1])=="-b") && argc == 3) {
        back(alias_of(string(argv[2])));
    }
    else if((string(argv[1])=="--recover" || string(argv[1])=="-R") && argc == 3) {
        recover(alias_of(string(argv[2])));
    }
    else if((string(argv[1])=="--show-info" || string(argv[1])=="-s") && argc == 3) {
        show_info(alias_of(string(argv[2])));
    }
    else if((string(argv[1])=="--delete" || string(argv[1])=="-d") && argc == 3) {
        delete_game(alias_of(string(argv[2])));
    }
    else if((string(argv[1])=="--edit" || string(argv[1])=="-e") && argc == 3) {
        edit_game(alias_of(string(argv[2])));
    }
    else if((string(argv[1])=="--alias" || string(argv[1])=="-A") && argc == 4) {
        create_alias(string(argv[2]), string(argv[3]));
    }
    else {
        std::cout << "Unknown command, plese type \"bluise -h\" to show help! \n";
    }
    bluise_core::saveGLL();
}