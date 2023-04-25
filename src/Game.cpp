#include "Game.h"
#include <filesystem>
#include "invalid_path.h"

void Game::set_working_directory(const string &wd)
{
    if(!std::filesystem::exists(wd)) {
        throw invalid_path("Invalid working directory!");
    }
    working_directory = wd;
}

void Game::set_executable(const string &e)
{
    if(!std::filesystem::exists(e)) {
        throw invalid_path("Invalid executable!");
    }
    executable = e;
}

void Game::set_save_path(const string &sp)
{
    if(!std::filesystem::exists(sp)) {
            throw invalid_path("Invalid save path!");
    }
    save_path = sp;
}

Game::Game(const string &n, const string &wd, const string &e, const string &sp) : name(n)
{
    set_working_directory(wd);
    set_executable(e);
    set_save_path(sp);

    if(e.substr(e.size()-4, 4)==".exe") { type = windows_exe; }
    else { type = linux_exe; }
}

void Game::execute()
{
    if(type==linux_exe) { 
        string command = "nohup "+ executable + " &";
        system(command.c_str());
    }
    else if(type==windows_exe) {
        string command = "nohup portproton \"" + executable + "\" &";
        system(command.c_str());
    }
}

bool Game::operator==(Game &other)
{
    return (this->name==other.name) ? true : false;
}

bool Game::operator==(string& other) {
    return (this->name==other) ? true : false;
}