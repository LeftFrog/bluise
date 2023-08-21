#include "ncurses.h"
#include <string>
#include <vector>
#include "buttons.h"

void make_info_win(const string& info_str) {
    clear();
    WINDOW* info = newwin(getmaxy(stdscr) - 2, getmaxx(stdscr) - 2 , 2, 2);
    refresh();
    box(info, 0, 0);
    mvwprintw(info, 1, (getmaxx(info) - info_str.length()) / 2, info_str.c_str());
    wattron(info, A_STANDOUT);
    mvwprintw(info, getmaxy(info) - 2, (getmaxx(info) - 4) / 2, "Back");
    wattroff(info, A_STANDOUT);
    char ch;
    while(ch = wgetch(info)) {
        switch(ch) 
        {
        case ENTER:
            delwin(info);
            return;
        }
    }
}

void make_info_win(const QVector<string> info_str) {
    clear();
    WINDOW* info = newwin(getmaxy(stdscr) - 2, getmaxx(stdscr) - 2 , 2, 2);
    refresh();
    box(info, 0, 0);
    for(int i = 0; i < info_str.size(); ++i) {
        mvwprintw(info, i+1, 1, info_str[i].c_str());
    }
    wattron(info, A_STANDOUT);
    mvwprintw(info, getmaxy(info) - 2, (getmaxx(info) - 4) / 2, "Back");
    wattroff(info, A_STANDOUT);
    char ch;
    while(ch = wgetch(info)) {
        switch(ch) 
        {
        case ENTER:
            delwin(info);
            return;
        }
    }
}