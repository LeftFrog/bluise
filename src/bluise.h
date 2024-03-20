#pragma once
#include <QList>
#include "Game.h"
#include <map>
#include "bluise_error.h"

namespace bluise_core {
extern QList<Game> games;
extern const QString DOCS;
extern const QString BACKUP_PATH;

template<typename Iterator>
void sort(Iterator begin, Iterator end);

void readGamesJSON();
void saveGamesJSON();

void back(const QString& name);
void recover(const QString& name);
}

namespace command_processor {
extern std::map<std::string, std::string> aliases;

void print_help();
void add_game();
void print_game_vector();
void back(const std::string& name);
void recover(const std::string& name);
void delete_game(const std::string& name);
void show_info(const std::string& name);
void run_game(const std::string& name);
void edit_game(std::string name);
void create_alias(const std::string& alias, const std::string& name);
const std::string alias_of(const std::string& alias);
void delete_alias(const std::string& alias);
void process_command_line(int argc, char** argv);

std::ostream& operator<<(std::ostream& os, std::map<std::string, std::string>& al);
std::istream& operator>>(std::istream& is, std::map<std::string, std::string>& al);
}
