#include "GameLine.h"

void GameLine::update_pos(int _y) {
    y = _y;
    menu.update_pos(y, x+game->get_name().length()+1);
}

void GameLine::print()
{
    mvwprintw(win, y, x, game->get_name().c_str());
}

void GameLine::print_menu()
{
    menu.print(win);
}

void GameLine::clear_menu() {
    mvwprintw(win, y, x+game->get_name().length()+1, "                                      ");
}

void GameLine::next()
{
    menu.next();
}

void GameLine::previous() 
{
    menu.previous();
}

int GameLine::enter()
{
    if(menu.button()==Menu::RUN) {
        game->execute();
        return 0;
    }
    else if(menu.button()==Menu::DELETE) {
        clear();
        WINDOW* sure = newwin(getmaxy(stdscr) / 2 , getmaxx(stdscr) / 2, getmaxy(stdscr) * 1 / 4, getmaxx(stdscr) * 1 / 4);
        refresh();
        box(sure, 0, 0);
        string ok = "Are you sure that you want delete " + game->get_name() + "? (y/n): ";
        mvwprintw(sure, 1, (getmaxx(sure) - ok.length()) / 2, ok.c_str());
        wattron(sure, A_STANDOUT);
        mvwprintw(sure, getmaxy(sure) - 2, getmaxx(sure) * 1 / 4, "YES");
        wattroff(sure, A_STANDOUT);
        mvwprintw(sure, getmaxy(sure) - 2, getmaxx(sure) * 3 / 4 - 1, "NO");
        bool yes = true;
        char c;
        while((c = wgetch(sure))) {
            switch(c) 
            {
            case 67:
            case 68:
            case 'a':
            case 'd':    
                if(yes) {
                    mvwprintw(sure, getmaxy(sure) - 2, getmaxx(sure) * 1 / 4, "YES");
                    wattron(sure, A_STANDOUT);
                    mvwprintw(sure, getmaxy(sure) - 2, getmaxx(sure) * 3 / 4 - 1, "NO");
                    wattroff(sure, A_STANDOUT);
                    yes = false;
                }
                else {
                    wattron(sure, A_STANDOUT);
                    mvwprintw(sure, getmaxy(sure) - 2, getmaxx(sure) * 1 / 4, "YES");
                    wattroff(sure, A_STANDOUT);
                    mvwprintw(sure, getmaxy(sure) - 2, getmaxx(sure) * 3 / 4 - 1, "NO");
                    yes = true;
                }
                break;
            case 10:
                return 1;
            }
        }
    }
}
