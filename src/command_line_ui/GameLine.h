#pragma once
#include "ncurses.h"
#include "../main/Game.h"
#include "string"
#include "Menu.h"

class GameLine {
private:
    WINDOW* win;
    Game* game;
    Menu menu;
    const static int x = 2;
    int y;
public:
    void print();
    void print_menu();
    void update_pos(int _y);
    string name() {return game->get_name();}
    void clear_menu();
    void next();
    void previous();
    int enter();
    GameLine(WINDOW* _win, Game* _game, const int& _y) : win(_win), game(_game), y(_y) { menu = Menu(x+game->get_name().length()+1, y); }
};