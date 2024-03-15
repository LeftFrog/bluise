#include "bluise.h"
#include <string>
#include <algorithm>
#include <fstream>
#include "GLLReader.h"
#include "invalid_path.h"
#include "gll_syntax_error.h"
#include <filesystem>
#include <QStandardPaths>

namespace bluise_core {
namespace fs = std::filesystem;
const string DOCS = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString()+"/Bluise/";
const string BACKUP_PATH = DOCS+"backs/";

QList<Game> games;

// std::sort does not work on my mac ¯⁠\⁠_⁠(⁠ツ⁠)⁠_⁠/⁠¯
template<typename Iterator>
Iterator part(Iterator begin, Iterator end) {
    auto previous = std::prev(end);
    auto i = begin;
    for(auto j = begin; j != previous; ++j) {
        if(*j < *previous) {
            std::swap(*i++, *j);
        }    
    }
    std::swap(*i, *previous);
}

template<typename Iterator>
void bluise_core::sort(Iterator begin, Iterator end)
{
    if(std::distance(begin, end)>1) {
        Iterator bound = part(begin, end);
        sort(begin, bound);
        sort(bound+1, end);
    }
}



void back(const string& name) {
    auto game = find(games.begin(), games.end(), name);

    if(game==games.end()) {
        throw bluise_error("There isn't this game!");
    }

    if(!fs::exists(BACKUP_PATH)) {
        fs::create_directories(BACKUP_PATH);
    }
    string back_path = BACKUP_PATH+name+"/";
    if(!fs::exists(back_path)) {
        if(!fs::create_directory(back_path)) {
            throw bluise_error("Can't create directory!");
        }
    }
    fs::copy(game->get_save_path(), back_path+".", fs::copy_options::recursive);
}

void recover(const string& name) {
    auto game = find(games.begin(), games.end(), name);

    if((game==games.end())) {
        throw bluise_error("There isn't this game!");
    }

    string back_path = BACKUP_PATH+name+"/";
    if(!fs::exists(back_path)) {
        throw bluise_error("There isn't backups of saves of your game");
    }
    fs::copy(back_path, game->get_save_path(), fs::copy_options::recursive | fs::copy_options::overwrite_existing);
}

void edit(const Game::var_type &var, const string &val, const string &name)
{
    auto game = find(games.begin(), games.end(), name);
    if(game==games.end()) {
        throw bluise_error("There isn't this game!");
    }
    switch(var) {
        case Game::var_type::name:
            game->set_name(val);
            break;
        case Game::var_type::working_directory:
            game->set_working_directory(val);
            break;
        case Game::var_type::executable:
            game->set_executable(val);
            break;
        case Game::var_type::save_path:
            game->set_save_path(val);
            break;
        default:
            throw bluise_error("Unknown variable!");
            break;
    }
}

void saveGLL() {
    if(!fs::exists(DOCS)) {
        fs::create_directories(DOCS);
    }
    sort(games.begin(), games.end());
    std::ofstream oft(DOCS+"Games.gll", std::ofstream::trunc);
    oft << games;
    oft.close();
}

void readGLL() {
    std::ifstream ist(DOCS+"Games.gll");
    try {
        games.clear();
        ist >> games;
    }
    catch (const invalid_path& err) {
        std::cerr << err.what();
    }
    catch (const gll_syntax_error& err) {
        std::cerr << err.what();
    }
    ist.close();
}

void add(const string &name, const string &working_directory, const string &executable, const string &save_path)
{
    auto game = find(games.begin(), games.end(), name);
    if (game!=games.end())
    {
        throw bluise_error("There is a game with the same name!");
    }
    games.push_back(Game(name, working_directory, executable, save_path));
}

void run(const string &name)
{
    auto game = find(games.begin(), games.end(), name);
    if(game==games.end()) {
        throw bluise_error("There isn't this game!");
    }
    game->execute();
}

void delete_game(const string &name)
{
    auto game = find(games.begin(), games.end(), name);
    if(game==games.end()) {
        throw bluise_error("There isn't this game!");
    }
    if(games.size()==1) {
        games.clear();
        return;
    }
    else {
        games.erase(game);
    }
}

}

namespace command_processor {
std::map<string, string> aliases;
std::map<string, Game::var_type> types = {  {"name", Game::var_type::name},
                                            {"working_directory", Game::var_type::working_directory},
                                            {"executable", Game::var_type::executable},
                                            {"save_path", Game::var_type::save_path}};

string splitter = "<------------------------------->";

std::ostream& operator<<(std::ostream& os, std::map<string, string>& al) {
    for(auto pair : al) {
        os << pair.first << " = " << pair.second << '\n';
    }
    return os;
}

std::istream& operator>>(std::istream& is, std::map<string, string>& al) {
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
    std::cout << splitter << std::endl;
    for(int i = 0; i < bluise_core::games.size(); ++i) {
        std::cout << i+1 << " | " << bluise_core::games[i].get_name() << std::endl;
    }
    std::cout << splitter << std::endl;
}

void back(const string& name) {
    try {
        bluise_core::back(name);
    } catch(const bluise_error& err) {
        std::cerr << err.what() << std::endl;
        return;
    }
    std::cout << "Successfully made backup of your saves.\n";
}

void recover(const string& name) {
    try {
        bluise_core::recover(name);
        std::cout << "Successfully recovered your saves.\n";
    } catch(const bluise_error& err) {
        std::cerr << err.what() << std::endl;
    }
}

void add_game() {
    string name = get_game_var("name");
    string working_directory = get_game_var("working_directory");
    string executable = get_game_var("executable");
    string save_path = get_game_var("save_path");

    try {
        bluise_core::add(name, working_directory, executable, save_path);
    }
    catch(const bluise_error& err) {
        std::cerr << err.what() << std::endl;
        return;
    }
    std::cout << "The game successfully added.\n";
}

void print_help() {
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
              <<    "--alias or -A {alias} {name of a game} - adds alias to game\n" \
              <<    "--delete-alias or -D {alias} - deletes alias of a game\n" \
              <<    splitter << std::endl;
}

void delete_game(const string& name) {
    std::cout << "Are you sure that you want delete " + name + "? (y/n): ";
    char answer;
    std::cin >> answer;
    if(!(answer=='y')) {
        return;
    }
    std::cout << std::endl;
    try {
        bluise_core::delete_game(name);
    }
    catch(const bluise_error& err) {
        std::cerr << err.what() << std::endl;
        return;
    }
    std::cout << "The game successfully deleted.\n";
}

void show_game_info(const QList<Game>::iterator& game) {
    std::cout   << splitter << std::endl << "Name: " + game->get_name()  << std::endl \
              << "Working directory: " + game->get_working_directory()  << std::endl\
              << "Executable: " + game->get_executable() << std::endl \
              << "Save path: " + game->get_save_path() << std::endl \
              << splitter << std::endl;
}

void show_info(const string& name) {
    auto game = find(bluise_core::games.begin(), bluise_core::games.end(), name);
    if(game==bluise_core::games.end()) {
        std::cout << "There isn't this game\n";
        return;
    }
    show_game_info(game);
}

void run_game(const string& name) {
    try {
        bluise_core::run(name);
    } catch(const bluise_error& err) {
        std::cerr << err.what() << std::endl;
        return;
    }
    std::cout << "Successfully ran the game.\n";
}

inline bool sure_change(const string& var, const string& val) {
    std::cout << "Are you sure that you want change " + var + " to " + val + "? (y/n): ";
    char answer;
    std::cin >> answer;
    return answer=='y' ? true : false;
}

void edit_game(string name) {
    QList<Game>::iterator game = find(bluise_core::games.begin(), bluise_core::games.end(), name);
    if(game==bluise_core::games.end()) {
        std::cout << "There isn't this game\n";
        return;
    }

    show_game_info(game);

    std::cout   << "Choose option to edit(name, working_directory, executable, save_path): \n";
    string var_name;
    std::cin >> var_name;
    std::cin.ignore();
    string val = get_game_var(var_name);
    Game::var_type var = types[var_name];
    try {
        bluise_core::edit(var, val, name);
    }
    catch (const bluise_error& err) {
        std::cerr << err.what();
    }
}

inline void load_aliases() {
    std::ifstream ist(bluise_core::DOCS+"aliases.txt");
    ist >> aliases;
}

inline void save_aliases() {
    std::ofstream oft(bluise_core::DOCS+"aliases.txt", std::ofstream::trunc);
    oft << aliases;
}

void create_alias(const string& alias, const string& name) {
    load_aliases();
    for(auto al : aliases) {
        if(al.first==alias) {
            std::cerr << "There is already this alias!\n";
            return;
        }
    }
    if(find(bluise_core::games.begin(), bluise_core::games.end(), name)==bluise_core::games.end()) {
        std::cerr << "There isn't this game!\n";
        return;
    }
    aliases[alias] = name;
    save_aliases();
}

const string alias_of(const string& alias) {
    load_aliases();
    string name;
    try {
        name = aliases.at(alias);
    } catch(std::out_of_range error) {
        return alias;
    }
    return name;
}

void delete_alias(const string& alias) {
    load_aliases();
    aliases.erase(alias);
    save_aliases();
}

void process_command_line(int argc, char** argv) {
    if(string(argv[1])=="--help" || string(argv[1])=="-h") {
        print_help();
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
    else if((string(argv[1])=="--delete-alias" || string(argv[1])=="-D") && argc == 3) {
        delete_alias(string(argv[2]));
    }
    else {
        std::cout << "Unknown command, plese type \"bluise -h\" to show help! \n";
    }
}
}