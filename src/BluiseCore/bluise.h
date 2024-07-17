#pragma once
#include "Game.h"
#include "bluise_error.h"
#include <QList>
#include <QJsonDocument>
#include <map>


namespace bluise_core {

extern const QString DOCS;
extern const QString BACKUP_PATH;



class GameManager : QObject {
    Q_OBJECT

public:
    GameManager(QObject* parent = nullptr);

    QList<Game> games;

    void loadGames(const QString& filename);
    void saveGames(const QString& filename);

    void makeBackup(const Game& game);
    void recover(const Game& game);

    bool gameExists(const QString& exectuable);

public slots:
    void addGames(const QList<Game>& games);

private: 
    QJsonDocument readGamesJSON(const QString& filename);
    void saveGamesJSON(const QString& filename, const QJsonArray& arr);
};

extern GameManager gameManager;

} 

namespace command_processor {
// extern std::map<std::string, std::string> aliases;

// void print_help();
// void add_game();
// void print_game_vector();
// void back(const std::string &name);
// void recover(const std::string &name);
// void delete_game(const std::string &name);
// void show_info(const std::string &name);
// void run_game(const std::string &name);
// void edit_game(std::string name);
// void create_alias(const std::string &alias, const std::string &name);
// const std::string alias_of(const std::string &alias);
// void delete_alias(const std::string &alias);
// void process_command_line(int argc, char **argv);

// std::ostream &operator<<(std::ostream &os,
//                          std::map<std::string, std::string> &al);
// std::istream &operator>>(std::istream &is,
//                          std::map<std::string, std::string> &al);
} // namespace command_processor
