#pragma once
#include <string>
#include <vector>
#include "ncurses.h"

using std::vector;
using std::string;

class Menu {
private:
    vector<string> buttons = {"Edit", "Run", "Show Info", "Back", "Recover","Delete"};
    int x, y;
    int current_button = EDIT;
public:
    enum {
            EDIT = 0,
            RUN,
            SHOWINFO,
            BACK,
            RECOVER,
            DELETE
        };
    Menu(const int& _x, const int& _y) : x(_x), y(_y) {}
    Menu() : x(0), y(0) {}
    void update_pos(int _y, int _x);
    void next();
    void previous();
    int button();
    void print(WINDOW* win); 
};