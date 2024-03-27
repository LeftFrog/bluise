#include "Game.h"
#include "bluise.h"
#include "invalid_path.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <filesystem>


void Game::set_working_directory(const QString &wd) {
  if (!QDir(wd).exists()) {
    throw invalid_path("Invalid working directory!");
  }
  if (wd[wd.size() - 1] != '/') {
    working_directory = wd + '/';
  } else {
    working_directory = wd;
  }
}

void Game::set_executable(const QString &e) {
#ifdef __APPLE__
  if (!std::filesystem::exists(e.toStdString())) {
    throw invalid_path("Invalid executable!");
  }
#else
  if (!std::filesystem::is_regular_file(e)) {
    throw invalid_path("Invalid executable!");
  }
#endif
  executable = e;
}

void Game::set_save_path(QString sp) {
  if (!QDir(sp).exists()) {
    throw invalid_path("Invalid save path!");
  }
  if (sp[sp.size() - 1] != '/') {
    sp += '/';
  }
  save_path = sp;
}

Game::Game(const QString &n, const QString &wd, const QString &e,
           const QString &sp, const QString &_header_name)
    : name(n), header_name(_header_name) {
  set_working_directory(wd);
  set_executable(e);
  set_save_path(sp);

  QString path = bluise_core::DOCS + "res/";
  if (QFile::exists(path + header_name)) {
    header_path = path + header_name;
  }
  if (e.toStdString().substr(e.size() - 4, 4) == ".exe") {
    type = windows_exe;
  } else {
    type = linux_exe;
  }
}

void Game::execute() const {
#ifdef __linux__
  if (type == linux_exe) {

    string command = "nohup \"" + executable + "\" &> /dev/null &";
    system(command.c_str());
  } else if (type == windows_exe) {
    string command = "nohup portproton \"" + executable + "\" &> /dev/null &";
    system(command.c_str());
  }
#elif __WIN32
  system(executable.c_str());
#elif __APPLE__
  qDebug() << executable;
  QString command = "open -a \"" + executable + "\"";
  system(command.toStdString().c_str());
#endif
}

bool Game::operator==(const Game &other) {
  return (this->name == other.name) ? true : false;
}

bool Game::operator==(const string &other) {
  return (this->name.toStdString() == other) ? true : false;
}

bool Game::operator==(const QString &other) {
  return (this->name == other) ? true : false;
}

bool Game::operator<(const Game &other) {
  return (this->name < other.name);
}
