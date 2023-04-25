#include "Game.h"
#include <filesystem>
#include "invalid_path.h"

Game::Game(string n, string wd, string e, string sp) : name(n) {
    if(!std::filesystem::exists(wd)) {
        throw invalid_path("Invalid working directory!");
    }
    working_directory = wd;
    if(!std::filesystem::exists(e)) {
        throw invalid_path("Invalid executable!");
    }
    executable = e;
    if(!std::filesystem::exists(sp)) {
            throw invalid_path("Invalid save path!");
    }
    save_path = sp;
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