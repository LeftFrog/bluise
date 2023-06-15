#pragma once
#include "ncurses.h"
#include "Game.h"
#include "string"
#include "Menu.h"

class GameLine {
private:
    WINDOW* win;
    Game* game;
    Menu menu;
    int x;
    int y;
public:
    void print();
    void print_menu();
    void clear_menu();
    void next();
    void previous();
    void enter(WINDOW* subwin);
    GameLine(WINDOW* _win, Game* _game, const int& _y, const int& _x) : win(_win), game(_game), x(_x), y(_y) { menu = Menu(x+game->get_name().length()+1, y); }
};