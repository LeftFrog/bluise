#pragma once
#include "Game.h"
#include <QList>
#include <QJsonDocument>

#include "../ModelView/GameListModel.h"
#include "../ModelView/GameProxyModel.h"

extern const QString DOCS;
extern const QString BACKUP_PATH;

class GameManager : QObject {
    Q_OBJECT

public:
    GameManager(QObject* parent = nullptr);

    QList<Game> games;
    GameListModel gameListModel;
    GameProxyModel gameProxyModel;

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