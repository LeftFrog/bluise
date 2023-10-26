#include "QGame.h"

QGame::QGame(const string& n, const string& wd, const string& e, const string& sp) : Game(n, wd, e, sp) {
    string path = bluise_core::HOME+"/Documents/Bluise/icons/";
    icon = std::filesystem::exists(path+name+".png") ? QIcon(string(path+name+".png").c_str()) : QIcon(string(path+"game.png").c_str());
    header = std::filesystem::exists(path+name+"_header.png") ? QPixmap(string(path+name+"_header.png").c_str()) : QPixmap(string(path+"game.png").c_str());
}

QGame::QGame(Game &game) : Game(game)
{
    string path = bluise_core::HOME+"/Documents/Bluise/icons/";
    icon = std::filesystem::exists(path+name+".png") ? QIcon(string(path+name+".png").c_str()) : QIcon(string(path+"game.png").c_str());
    header = std::filesystem::exists(path+name+"_header.png") ? QPixmap(string(path+name+"_header.png").c_str()) : QPixmap(string(path+"game.png").c_str());
}
