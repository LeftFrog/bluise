#include "bluise.h"
#include "../command_line_ui/ncurses_ui.cpp"
//#include "../command_line/command_processor.cpp"
namespace bluise_core {
void back(const string& name) {
    auto game = find(games.begin(), games.end(), name);

    if(game==games.end()) {
        throw bluise_error("There isn't this game!");
    }

    string back_path = HOME+"/Documents/Bluise/backs/"+name+"/";
    if(!fs::exists(back_path)) {
        if(!fs::create_directory(back_path)) {
            throw bluise_error("Can't create directory!");
        }
    }
    std::system(string("cp -R \""+game->get_save_path()+".\" \""+back_path+"\"").c_str());
}

void recover(const string& name) {
    auto game = find(games.begin(), games.end(), name);

    if((game==games.end())) {
        throw bluise_error("There isn't this game!");
    }

    string back_path = HOME+"/Documents/Bluise/backs/"+name+"/";
    if(!fs::exists(back_path)) {
        throw bluise_error("There isn't backups of saves of your game");
    }
    std::system(string("cp -R \""+back_path+".\" \""+game->get_save_path()+"\"").c_str());
}

void edit(const string &var, const string &val, const string &name)
{
    auto game = find(games.begin(), games.end(), name);
    if(var=="name") {
        game->set_name(val);
    }
    else if(var=="working_directory") {
        game->set_working_directory(val);
    }
    else if(var=="executable") {
        game->set_executable(val);
    }
    else if(var=="save_path") {
        game->set_save_path(val);
    }
    else {
        throw bluise_error("Unknown variable!");
    }
}

inline void saveGLL() {
    sort(games.begin(), games.end());
    ofstream oft(HOME+"/Documents/Bluise/Games.gll", std::ofstream::trunc);
    oft << games;
    oft.close();
}

inline void readGLL() {

    ifstream ist(HOME+"/Documents/Bluise/Games.gll");
    try {
        games.clear();
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
    games.erase(game);
}

}

int main(int argc, char** argv) {  

    bluise_core::readGLL();
    if(argc==1) {
        print_ui();
    }
    else {
        process_command_line(argc, argv);
    }

    return 0;
}