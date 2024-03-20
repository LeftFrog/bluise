#pragma once
#include <QWidget>
#include "Game.h"
#include "GameOptionWidget.h"

class GameEditWidget : public QWidget {
    Q_OBJECT

public:
    GameEditWidget(Game* _game, QWidget* parent = nullptr);
private:
    Game* game;
    GameOptionWidget* name;
    GameOptionWidget* working_directory;
    GameOptionWidget* exec;
    GameOptionWidget* save_path;
private slots:
    void closeWin();
    void apply();
signals:
    void gameChanged();
};