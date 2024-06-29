#include "Game.h"
#include "bluise.h"
#include "invalid_path.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <filesystem>

void Game::setWorkingDirectory(const QString &wd) {
    if (!QDir(wd).exists()) {
        throw invalid_path("Invalid working directory!");
    }
    if (wd[wd.size() - 1] != '/') {
        workingDirectory = wd + '/';
    } else {
        workingDirectory = wd;
    }
}

void Game::setExecutable(const QString &e) {
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

void Game::setSavePath(QString sp) {
  if (!QDir(sp).exists()) {
    throw invalid_path("Invalid save path!");
  }
  if (sp[sp.size() - 1] != '/') {
    sp += '/';
  }
  savePath = sp;
}

void Game::setCover(const QString &_coverName) {
  QString path = bluise_core::DOCS + "res/covers/";
  if (QFile::exists(path + _coverName)) {
    coverPath = path + _coverName;
    cover = QPixmap(coverPath);
    coverName = _coverName;
  }
}

Game::Game() {
  name = "";
  workingDirectory = "";
  executable = "";
  savePath = "";
  headerPath = "";
  headerName = "";
  releaseYear = 0;
}

Game::Game(const QString& _name, const QString& _executable) {
  name = _name;
  setExecutable(_executable);
  workingDirectory = "";
  savePath = "";
  headerPath = "";
  headerName = "";
  releaseYear = 0;
}

Game::Game(const QString &n, const QString &e, const QString &wd,
           const QString &sp, const QString &_coverName, bool _disabled)
    : name(n), coverName(_coverName), disabled(_disabled) {
  if (_disabled) {
    workingDirectory = wd;
    executable = e;
    savePath = sp;
  } else {
    setWorkingDirectory(wd);
    setExecutable(e);
    setSavePath(sp);
  }
  QString path = bluise_core::DOCS + "res/covers/";
  if (QFile::exists(path + coverName)) {
    coverPath = path + coverName;
  }
  releaseYear = 0;
  // header = QPixmap(headerPath).scaled(390, 234, Qt::KeepAspectRatio);
  cover = QPixmap(coverPath);
  runner = Native;
}

void Game::execute() const {
#ifdef __linux__
  string command = "nohup \"" + executable + "\" &> /dev/null &";
  system(command.c_str());
#elif __WIN32
  system(executable.c_str());
#elif __APPLE__
  qDebug() << executable;
  QString command = "open -a \"" + executable + "\"";
  system(command.toStdString().c_str());
#endif
}

bool Game::operator==(const Game &other) const {
  return (this->name == other.name) ? true : false;
}

bool Game::operator==(const string &other) const {
  return (this->name.toStdString() == other) ? true : false;
}

bool Game::operator==(const QString &other) const {
  return (this->name == other) ? true : false;
}

bool Game::operator<(const Game &other) const {
  return (this->name < other.name);
}