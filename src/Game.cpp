#include "Game.h"

Game::Game(string n, string wd, string e, string sv) : name(n), working_directory(wd), executable(e), save_path(sv)  {}

bool Game::operator==(Game& other) {
    return (this->name==other.name) ? true : false;
}

bool Game::operator==(string& other) {
    return (this->name==other) ? true : false;
}