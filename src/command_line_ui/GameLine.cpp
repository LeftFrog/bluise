#include "GameLine.h"
#include "buttons.h"
#include "../main/bluise.h"

void GameLine::update_pos(int _y) {
    y = _y;
    menu.update_pos(y, x+game.get_name().length()+1);
}

void GameLine::print_menu()
{
    menu.print(win);
}

void GameLine::clear_menu() {
    mvwprintw(win, y, x+game.get_name().length()+1, "                                      ");
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
        game.execute();
        return 0;
    }
    else if(menu.button()==Menu::DELETE) {
        clear();
        WINDOW* sure = newwin(getmaxy(stdscr) / 2 , getmaxx(stdscr) / 2, getmaxy(stdscr) * 1 / 4, getmaxx(stdscr) * 1 / 4);
        refresh();
        box(sure, 0, 0);
        string ok = "Are you sure that you want delete " + game.get_name() + "? (y/n): ";
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
            case RIGHT_ARROW:
            case LEFT_ARROW:
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
            case ENTER:
                delwin(sure);
                return 1;
            }
        }
    }
    else if(menu.button()==Menu::SHOWINFO) {
        clear();
        WINDOW* info = newwin(getmaxy(stdscr) - 2, getmaxx(stdscr) - 2 , 2, 2);
        refresh();
        box(info, 0, 0);
        mvwprintw(info, 2, 2, string("Name: " + game.get_name()).c_str());
        mvwprintw(info, 4, 2, string("Working directory: " + game.get_working_directory()).c_str());
        mvwprintw(info, 6, 2, string("Executable: " + game.get_executable()).c_str());
        mvwprintw(info, 8, 2, string("Save path: " + game.get_save_path()).c_str());
        wattron(info, A_STANDOUT);
        mvwprintw(info, getmaxy(info) - 2, getmaxx(info) / 2 - 6, "Back");
        wattroff(info, A_STANDOUT);
        char ch;
        while(ch = wgetch(info)) {
            switch(ch) 
            {
            case ENTER:
                delwin(info);
                return 0;
            }
        }
    }
    else if(menu.button()==Menu::BACK) {
        WINDOW* ok = newwin(getmaxy(stdscr) / 2 , getmaxx(stdscr) / 2, getmaxy(stdscr) * 1 / 4, getmaxx(stdscr) * 1 / 4);
        refresh();
        box(ok, 0, 0);
        mvwprintw(ok, getmaxy(ok) / 2, getmaxx(ok) / 2 - game.get_name().length() - 2, game.get_name().c_str());
        wattron(ok, A_STANDOUT);
        mvwprintw(ok, getmaxy(ok) - 2, getmaxx(ok) / 2 - 6, "Back");
        wattroff(ok, A_STANDOUT);
        char ch;
        while(ch = wgetch(ok)) {
            switch(ch) 
            {
            case ENTER:
                delwin(ok);
                return 2;
            }
        }
    }
}

