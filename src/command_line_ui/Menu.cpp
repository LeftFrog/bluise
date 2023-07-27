#include "Menu.h"

void Menu::update_pos(int _y, int _x) {
    y = _y;
    x = _x;
}

void Menu::print(WINDOW* win)
{
    int _x = x;
    for(int i = 0; i < buttons.size(); ++i) {
        if(i==current_button) {
            wattron(win, A_STANDOUT);
            mvwprintw(win, y, _x, string(buttons[i]).c_str());
            wattroff(win, A_STANDOUT);
        }
        else {
            mvwprintw(win, y, _x, string(buttons[i]).c_str());
        }
        _x += (buttons[i].length()+1);
        mvwprintw(win, y, _x-1, "");
    }
}

void Menu::next()
{
    if(current_button==DELETE) {
        current_button=EDIT;
    }
    else {
        current_button++;
    }
}

void Menu::previous()
{
    if(current_button==EDIT) {
        current_button=DELETE;
    }
    else {
        current_button--;
    }
}

int Menu::button()
{
    return current_button;
}
