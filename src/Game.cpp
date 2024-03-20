#include "Game.h"
#include <filesystem>
#include "bluise.h"
#include "invalid_path.h"
#include <QDebug>
#include <QFile>
#include <QDir>

void Game::set_working_directory(const QString &wd) {
    if(!QDir(wd).exists()) {
        throw invalid_path("Invalid working directory!");
    }
    if (wd[wd.size()-1] != '/') {
        working_directory = wd + '/';
    }
    else {
        working_directory = wd;
    }
}

void Game::set_executable(const QString &e) {
#ifdef __APPLE__
    if(!std::filesystem::exists(e.toStdString())) {
        throw invalid_path("Invalid executable!");
    }
#else
    if(!std::filesystem::is_regular_file(e)) {
        throw invalid_path("Invalid executable!");
    }
#endif
    executable = e;
}

void Game::set_save_path(QString sp) {
    if(!QDir(sp).exists()) {
            throw invalid_path("Invalid save path!");
    }
    if(sp[sp.size()-1] != '/') {
        sp += '/';
    }
    save_path = sp;
}

Game::Game(const QString &n, const QString &wd, const QString &e, const QString &sp) : name(n) {
    set_working_directory(wd);
    set_executable(e);
    set_save_path(sp);

    QString path = bluise_core::DOCS+"res/";
    //icon = std::filesystem::exists(path+name+".png") ? QIcon(string(path+name+".png").c_str()) : QIcon(string(path+"game.png").c_str());
    header_path = QFile::exists(path+name+"_header.jpg") ? path+name+"_header.jpg" : path+name+"_header.jpg";
    if(e.toStdString().substr(e.size()-4, 4)==".exe") { type = windows_exe; }
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
        qDebug() << executable;
        QString command = "open -a \""+executable+"\"";
        system(command.toStdString().c_str());
#endif
}

bool Game::operator==(const Game &other)
{
    return (this->name==other.name) ? true : false;
}

bool Game::operator==(const string& other) {

    return (this->name.toStdString()==other) ? true : false;
}

bool Game::operator==(const QString & other)
{
    return (this->name==other) ? true : false;
}

bool Game::operator<(const Game& other) {
    return (this->name<other.name) ? true : false;
}
