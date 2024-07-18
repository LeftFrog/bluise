#include "bluise.h"
#include "invalid_path.h"
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

const QString DOCS = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Bluise/";
const QString BACKUP_PATH = DOCS + "backs/";

void GameManager::addGames(const QList<Game>& games) {
    this->games.append(games);
    std::sort(this->games.begin(), this->games.end());
}

GameManager::GameManager(QObject* parent) : QObject(parent), gameListModel(), gameProxyModel() {
}

void GameManager::loadGames(const QString& filename) {
  QJsonDocument doc = readGamesJSON(filename);
  QJsonArray arr = doc.array();
  games.clear();
  for (auto game : arr) {
    QJsonObject obj = game.toObject();
    Game g;
    try {
      g = Game(obj["name"].toString(), obj["executable"].toString(),
                obj["workingDirectory"].toString(), obj["savePath"].toString(),
                  obj["coverName"].toString());
    } catch (const bluise_error& err) {
      std::cerr << err.what() << std::endl;
      g = Game(obj["name"].toString(), obj["executable"].toString(),
                obj["workingDirectory"].toString(), obj["savePath"].toString(),
                obj["coverName"].toString(), true);
      g.setRunner(static_cast<Game::Runner>(obj["runner"].toInt()));
    }
  g.setReleaseYear(obj["releaseYear"].toInt());
  games.push_back(g);
  }
  std::sort(games.begin(), games.end());
}

void GameManager::saveGames(const QString& filename) {
  std::sort(games.begin(), games.end());
  QJsonArray arr;
  for (auto game : games) {
    QJsonObject obj;
    obj["name"] = game.getName();
    obj["workingDirectory"] = game.getWorkingDirectory();
    obj["executable"] = game.getExecutable();
    obj["savePath"] = game.getSavePath();
    obj["coverName"] = game.getCoverName();
    obj["releaseYear"] = game.getReleaseYear();
    obj["runner"] = game.getRunner();
    arr.append(obj);
  }
  saveGamesJSON(filename, arr);
}

void GameManager::makeBackup(const Game& game) {
  QDir dir(BACKUP_PATH);
  if (!dir.exists()) {
    dir.mkdir(BACKUP_PATH);
  }
  QString back_path = BACKUP_PATH + game.getName() + "/";
  QDir back_dir(back_path);
  if (!back_dir.exists()) {
    if (!back_dir.mkdir(back_path)) {
      throw bluise_error("Can't create directory!");
    }
  }
  fs::copy(game.getSavePath().toStdString(), (back_path + ".").toStdString(),
           fs::copy_options::recursive);
}

void GameManager::recover(const Game& game) {
  QString back_path = BACKUP_PATH + game.getName() + "/";
  QDir back_dir(back_path);
  if (!back_dir.exists()) {
    throw bluise_error("There isn't backups of saves of your game");
  }
  fs::copy(back_path.toStdString(), game.getSavePath().toStdString(),
           fs::copy_options::recursive | fs::copy_options::overwrite_existing);
}

bool GameManager::gameExists(const QString& exectuable) {
  for (auto game : games) {
    if (game.getExecutable() == exectuable) {
      return true;
    }
  }
  return false;
}

QJsonDocument GameManager::readGamesJSON(const QString& filename) {
  QString str;
  QFile file;
  file.setFileName(filename);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  str = file.readAll();
  file.close();
  return QJsonDocument::fromJson(str.toUtf8());
}

void GameManager::saveGamesJSON(const QString& filename, const QJsonArray& arr) {
  QJsonDocument doc(arr);
  QFile file(filename);
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  file.resize(0);
  file.write(doc.toJson());
  file.close();
}

GameManager gameManager = GameManager();