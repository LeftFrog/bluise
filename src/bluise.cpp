#include "bluise.h"
#include "invalid_path.h"
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace bluise_core {
namespace fs = std::filesystem;
const QString DOCS =
    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
    "/Bluise/";
const QString BACKUP_PATH = DOCS + "backs/";

QList<Game> games;

// std::sort does not work on my mac ¯⁠\⁠_⁠(⁠ツ⁠)⁠_⁠/⁠¯
template <typename Iterator, typename Compare> 
Iterator part(Iterator begin, Iterator end, Compare comp) {
  auto previous = std::prev(end, 1);
  auto i = begin;
  for (auto j = begin; j != previous; ++j) {
    if (comp(*j, *previous)) {
      std::swap(*i++, *j);
    }
  }
  std::swap(*i, *previous);
  return i;
}

template <typename Iterator, typename Compare> 
void sort(Iterator begin, Iterator end, Compare comp) {
  if (std::distance(begin, end) > 1) {
    Iterator bound = part(begin, end, comp);
    sort(begin, bound, comp);
    sort(bound + 1, end, comp);
  }
}

void back(const QString &name) {
  auto game = find(games.begin(), games.end(), name.toStdString());

  if (game == games.end()) {
    throw bluise_error("There isn't this game!");
  }
  QDir dir(BACKUP_PATH);
  if (!dir.exists()) {
    dir.mkdir(BACKUP_PATH);
  }
  QString back_path = BACKUP_PATH + name + "/";
  QDir back_dir(back_path);
  if (!back_dir.exists()) {
    if (!back_dir.mkdir(back_path)) {
      throw bluise_error("Can't create directory!");
    }
  }
  fs::copy(game->get_save_path().toStdString(), (back_path + ".").toStdString(),
           fs::copy_options::recursive);
}

void recover(const QString &name) {
  auto game = find(games.begin(), games.end(), name.toStdString());

  if ((game == games.end())) {
    throw bluise_error("There isn't this game!");
  }

  QString back_path = BACKUP_PATH + name + "/";
  QDir back_dir(back_path);
  if (!back_dir.exists()) {
    throw bluise_error("There isn't backups of saves of your game");
  }
  fs::copy(back_path.toStdString(), game->get_save_path().toStdString(),
           fs::copy_options::recursive | fs::copy_options::overwrite_existing);
}

void readGamesJSON() {
  QString str;
  QFile file;
  file.setFileName(DOCS + "Games.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  str = file.readAll();
  file.close();
  QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
  QJsonArray arr = doc.array();
  for (auto game : arr) {
    QJsonObject obj = game.toObject();
    try {
      games.push_back(
          Game(obj["name"].toString(), obj["working_directory"].toString(),
               obj["executable"].toString(), obj["save_path"].toString(),
               obj["header"].toString()));
    } catch (const invalid_path &err) {
      std::cerr << err.what() << std::endl;
    }
  }
}

void saveGamesJSON() {
  bluise_core::sort(games.begin(), games.end(), [](const Game &a, const Game &b) {
    return a.get_name() < b.get_name();
  });
  QJsonArray arr;
  for (auto game : games) {
    QJsonObject obj;
    obj["name"] = game.get_name();
    obj["working_directory"] = game.get_working_directory();
    obj["executable"] = game.get_executable();
    obj["save_path"] = game.get_save_path();
    obj["header"] = game.get_header_name();
    arr.append(obj);
  }
  QJsonDocument doc(arr);
  QFile file(DOCS + "Games.json");
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  file.resize(0);
  file.write(doc.toJson());
  file.close();
}

} // namespace bluise_core

namespace command_processor {
namespace bc = bluise_core;

std::map<string, string> aliases;
std::map<string, Game::var_type> types = {
    {"name", Game::var_type::name},
    {"working_directory", Game::var_type::working_directory},
    {"executable", Game::var_type::executable},
    {"save_path", Game::var_type::save_path}};

string splitter = "<------------------------------->";

std::ostream &operator<<(std::ostream &os, std::map<string, string> &al) {
  for (auto pair : al) {
    os << pair.first << " = " << pair.second << '\n';
  }
  return os;
}

std::istream &operator>>(std::istream &is, std::map<string, string> &al) {
  string line;
  while (!is.eof()) {
    getline(is, line);
    int pos = line.find('=');
    if (pos == string::npos) {
      return is;
    }
    al[line.substr(0, pos - 1)] = line.substr(pos + 2, line.length() - 1);
  }
  return is;
}

inline string get_game_var(const string &var_name) {
  std::cout << "Enter a " + var_name + " of a game: \n";
  string var;
  std::getline(std::cin, var);
  return var;
}

void print_game_vector() {
  std::cout << splitter << std::endl;
  for (int i = 0; i < bluise_core::games.size(); ++i) {
    std::cout << i + 1 << " | "
              << bluise_core::games[i].get_name().toStdString() << std::endl;
  }
  std::cout << splitter << std::endl;
}

void back(const string &name) {
  try {
    bluise_core::back(QString::fromStdString(name));
  } catch (const bluise_error &err) {
    std::cerr << err.what() << std::endl;
    return;
  }
  std::cout << "Successfully made backup of your saves.\n";
}

void recover(const string &name) {
  try {
    bluise_core::recover(QString::fromStdString(name));
    std::cout << "Successfully recovered your saves.\n";
  } catch (const bluise_error &err) {
    std::cerr << err.what() << std::endl;
  }
}

void add_game() {
  string name = get_game_var("name");
  string working_directory = get_game_var("working_directory");
  string executable = get_game_var("executable");
  string save_path = get_game_var("save_path");

  try {
    auto game = find(bc::games.begin(), bc::games.end(), name);
    if (game != bc::games.end()) {
      throw bluise_error("There is a game with the same name!");
    }
    bc::games.push_back(Game(
        QString::fromStdString(name), QString::fromStdString(working_directory),
        QString::fromStdString(executable), QString::fromStdString(save_path)));
  } catch (const bluise_error &err) {
    std::cerr << err.what() << std::endl;
    return;
  }
  std::cout << "The game successfully added.\n";
}

void print_help() {
  std::cout << splitter << "\nCommands: \n"
            << "--help or -h - shows this list of the commands\n"
            << "--list or -l - shows the list of games\n"
            << "--add or -a - adds a game to the list\n"
            << "--run or -r {name of a game} - runs game\n"
            << "--back or -b {name of a game} - makes backup of your saves\n"
            << "--recover or -R {name of a game} - recover syour saves\n"
            << "--show-info or -s {name of a game} - shows info about a game\n"
            << "--delete or -d {name of a game} - deletes game from list\n"
            << "--edit or -e {name of a game} - edits your game\n"
            << "--alias or -A {alias} {name of a game} - adds alias to game\n"
            << "--delete-alias or -D {alias} - deletes alias of a game\n"
            << splitter << std::endl;
}

void delete_game(const string &name) {
  std::cout << "Are you sure that you want delete " + name + "? (y/n): ";
  char answer;
  std::cin >> answer;
  if (!(answer == 'y')) {
    return;
  }
  std::cout << std::endl;
  try {
    auto game = find(bc::games.begin(), bc::games.end(), name);
    if (game == bc::games.end()) {
      throw bluise_error("There isn't this game!");
    }
    if (bc::games.size() == 1) {
      bc::games.clear();
      return;
    } else {
      bc::games.erase(game);
    }
  } catch (const bluise_error &err) {
    std::cerr << err.what() << std::endl;
    return;
  }
  std::cout << "The game successfully deleted.\n";
}

void show_game_info(const QList<Game>::iterator &game) {
  std::cout << splitter << std::endl
            << "Name: " + game->get_name().toStdString() << std::endl
            << "Working directory: " +
                   game->get_working_directory().toStdString()
            << std::endl
            << "Executable: " + game->get_executable().toStdString()
            << std::endl
            << "Save path: " + game->get_save_path().toStdString() << std::endl
            << splitter << std::endl;
}

void show_info(const string &name) {
  auto game = find(bc::games.begin(), bc::games.end(), name);
  if (game == bc::games.end()) {
    std::cout << "There isn't this game\n";
    return;
  }
  show_game_info(game);
}

void run_game(const string &name) {
  try {
    auto game = find(bc::games.begin(), bc::games.end(), name);
    if (game == bc::games.end()) {
      throw bluise_error("There isn't this game!");
    }
    game->execute();
  } catch (const bluise_error &err) {
    std::cerr << err.what() << std::endl;
    return;
  }
  std::cout << "Successfully ran the game.\n";
}

inline bool sure_change(const string &var, const string &val) {
  std::cout << "Are you sure that you want change " + var + " to " + val +
                   "? (y/n): ";
  char answer;
  std::cin >> answer;
  return answer == 'y' ? true : false;
}

void edit_game(string name) {
  QList<Game>::iterator game = find(bc::games.begin(), bc::games.end(), name);
  if (game == bc::games.end()) {
    std::cout << "There isn't this game\n";
    return;
  }

  show_game_info(game);

  std::cout << "Choose option to edit(name, working_directory, executable, "
               "save_path): \n";
  string var_name;
  std::cin >> var_name;
  std::cin.ignore();
  string val = get_game_var(var_name);
  Game::var_type var = types[var_name];
  try {
    switch (var) {
    case Game::var_type::name:
      game->set_name(QString::fromStdString(val));
      break;
    case Game::var_type::working_directory:
      game->set_working_directory(QString::fromStdString(val));
      break;
    case Game::var_type::executable:
      game->set_executable(QString::fromStdString(val));
      break;
    case Game::var_type::save_path:
      game->set_save_path(QString::fromStdString(val));
      break;
    default:
      throw bluise_error("Unknown variable!");
      break;
    }
  } catch (const bluise_error &err) {
    std::cerr << err.what();
  }
}

inline void load_aliases() {
  std::ifstream ist(bluise_core::DOCS.toStdString() + "aliases.txt");
  ist >> aliases;
}

inline void save_aliases() {
  std::ofstream oft(bluise_core::DOCS.toStdString() + "aliases.txt",
                    std::ofstream::trunc);
  oft << aliases;
}

void create_alias(const string &alias, const string &name) {
  load_aliases();
  for (auto al : aliases) {
    if (al.first == alias) {
      std::cerr << "There is already this alias!\n";
      return;
    }
  }
  if (find(bluise_core::games.begin(), bluise_core::games.end(), name) ==
      bluise_core::games.end()) {
    std::cerr << "There isn't this game!\n";
    return;
  }
  aliases[alias] = name;
  save_aliases();
}

const string alias_of(const string &alias) {
  load_aliases();
  string name;
  try {
    name = aliases.at(alias);
  } catch (std::out_of_range error) {
    return alias;
  }
  return name;
}

void delete_alias(const string &alias) {
  load_aliases();
  aliases.erase(alias);
  save_aliases();
}

void process_command_line(int argc, char **argv) {
  if (string(argv[1]) == "--help" || string(argv[1]) == "-h") {
    print_help();
  } else if (string(argv[1]) == "--add" || string(argv[1]) == "-a") {
    add_game();
  } else if (string(argv[1]) == "--list" || string(argv[1]) == "-l") {
    print_game_vector();
  } else if ((string(argv[1]) == "--run" || string(argv[1]) == "-r") &&
             argc == 3) {
    run_game(alias_of(string(argv[2])));
  } else if ((string(argv[1]) == "--back" || string(argv[1]) == "-b") &&
             argc == 3) {
    back(alias_of(string(argv[2])));
  } else if ((string(argv[1]) == "--recover" || string(argv[1]) == "-R") &&
             argc == 3) {
    recover(alias_of(string(argv[2])));
  } else if ((string(argv[1]) == "--show-info" || string(argv[1]) == "-s") &&
             argc == 3) {
    show_info(alias_of(string(argv[2])));
  } else if ((string(argv[1]) == "--delete" || string(argv[1]) == "-d") &&
             argc == 3) {
    delete_game(alias_of(string(argv[2])));
  } else if ((string(argv[1]) == "--edit" || string(argv[1]) == "-e") &&
             argc == 3) {
    edit_game(alias_of(string(argv[2])));
  } else if ((string(argv[1]) == "--alias" || string(argv[1]) == "-A") &&
             argc == 4) {
    create_alias(string(argv[2]), string(argv[3]));
  } else if ((string(argv[1]) == "--delete-alias" || string(argv[1]) == "-D") &&
             argc == 3) {
    delete_alias(string(argv[2]));
  } else {
    std::cout << "Unknown command, plese type \"bluise -h\" to show help! \n";
  }
}
} // namespace command_processor