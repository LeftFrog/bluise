#include "Game.h"
#include <filesystem>
#include "bluise.h"
#include "invalid_path.h"

void Game::set_working_directory(const string &wd) {
    if(!std::filesystem::exists(wd)) {
        throw invalid_path("Invalid working directory!");
    }
    working_directory = wd;
}

void Game::set_executable(const string &e) {
#ifdef __APPLE__
    if(!std::filesystem::exists(e)) {
        throw invalid_path("Invalid executable!");
    }
#else
    if(!std::filesystem::is_regular_file(e)) {
        throw invalid_path("Invalid executable!");
    }
#endif
    executable = e;
}

void Game::set_save_path(string sp) {
    if(!std::filesystem::exists(sp)) {
            throw invalid_path("Invalid save path!");
    }
    if(sp[sp.size()-1] != '/') {
        sp += '/';
    }
    save_path = sp;
}

Game::Game(const string &n, const string &wd, const string &e, const string &sp) : name(n) {
    set_working_directory(wd);
    set_executable(e);
    set_save_path(sp);

    string path = bluise_core::DOCS+"res/";
    //icon = std::filesystem::exists(path+name+".png") ? QIcon(string(path+name+".png").c_str()) : QIcon(string(path+"game.png").c_str());
    header_path = std::filesystem::exists(path+name+"_header.jpg") ? QString::fromStdString(path+name+"_header.jpg") : QString::fromStdString(path+name+"_header.jpg");

    if(e.substr(e.size()-4, 4)==".exe") { type = windows_exe; }
    else { type = linux_exe; }
}

void Game::execute() const {
#ifdef __linux__
    if(type==linux_exe) {

        string command = "nohup \""+ executable + "\" &> /dev/null &";
        system(command.c_str());
    }
    else if(type==windows_exe) {
        string command = "nohup portproton \"" + executable + "\" &> /dev/null &";
        system(command.c_str());
    }
#elif __WIN32
        system(executable.c_str());
#elif __APPLE__
        string command = "open -a "+executable;
        system(command.c_str());
#endif
}

bool Game::operator==(const Game &other)
{
    return (this->name==other.name) ? true : false;
}

bool Game::operator==(const string& other) {

    return (this->name==other) ? true : false;
}

bool Game::operator<(const Game& other) {
    return (this->name<other.name) ? true : false;
}
