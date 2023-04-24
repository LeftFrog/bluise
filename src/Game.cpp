#include "Game.h"

Game::Game(string n, string wd, string e, string sv) : name(n), working_directory(wd), executable(e), save_path(sv)  {
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