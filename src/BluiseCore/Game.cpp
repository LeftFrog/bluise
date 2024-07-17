#include "Game.h"
#include "bluise.h"
#include "invalid_path.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <filesystem>

bool Game::isValidDirectory(const QString& path) {
  return QDir(path).exists();
} 

bool Game::isValidExecutable(const QString& path) {
#ifdef __APPLE__
  return std::filesystem::exists(path.toStdString());
#else
  return std::filesystem::is_regular_file(path);
#endif
}


void Game::setWorkingDirectory(const QString &wd) {
    if (!isValidDirectory(wd)) {
        throw invalid_path("Invalid working directory!");
    }
    workingDirectory = wd.endsWith('/') || wd.isEmpty() ? wd : wd + '/';
}

void Game::setExecutable(const QString &e) {
  if (!isValidExecutable(e)) {
    throw invalid_path("Invalid executable!");
  }
  executable = e;
}

void Game::setSavePath(QString sp) {
  if (!isValidDirectory(sp)) {
    throw invalid_path("Invalid save path!");
  }
  savePath = sp.endsWith('/') || sp.isEmpty()? sp : sp + '/';
}

void Game::setCover(const QString &_coverName) {
  QString path = DOCS + "res/covers/";
  QString fullPath = path + _coverName;
  if (QFile::exists(fullPath)) {
    coverPath = fullPath;
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
  coverPath = "";
  coverName = "";
  releaseYear = 0;
  disabled = true;
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
  setCover(_coverName);
  releaseYear = 0;
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