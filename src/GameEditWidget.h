#pragma once
#include <QWidget>
#include "Game.h"

class GameEditWidget : public QWidget {
    Q_OBJECT

public:
    GameEditWidget(Game* _game, QWidget* parent = nullptr);
private:
    Game* game;
private slots:
    void open_file();
    void closeWin();
};