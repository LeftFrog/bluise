#include "GameLine.h"

void GameLine::update_pos(int _y) {
    y = _y;
    menu.update_pos(y, x+game->get_name().length()+1);
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
                if(yes) {
                    bluise_core::delete_game(game->get_name());
                    bluise_core::saveGLL();
                }
                return 1;
            }
        }
    }
    else if(menu.button()==Menu::SHOWINFO) {
        vector<string> info = { "Name: " + game->get_name(), 
                                "Working directory: " + game->get_working_directory(), 
                                "Executable: " + game->get_executable(), 
                                "Save path: " + game->get_save_path()};
        make_info_win(info);
    }
    else if(menu.button()==Menu::BACK) {
        clear();
        WINDOW* sure = newwin(getmaxy(stdscr) / 2 , getmaxx(stdscr) / 2, getmaxy(stdscr) * 1 / 4, getmaxx(stdscr) * 1 / 4);
        refresh();
        box(sure, 0, 0);
        string ok = "Do you want to back up saves for the "+game->get_name()+"?";
        mvwprintw(sure, 1, (getmaxx(sure) - ok.length()) / 2, ok.c_str());
        wattron(sure, A_STANDOUT);
        mvwprintw(sure, getmaxy(sure) - 2, getmaxx(sure) * 1 / 4, "YES");
        wattroff(sure, A_STANDOUT);
        mvwprintw(sure, getmaxy(sure) - 2, getmaxx(sure) * 3 / 4 - 1, "NO");
        bool yes = true;
        char ch;
        while(ch = wgetch(sure)) {
            switch(ch) 
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
                if(yes) {
                    bluise_core::back(game->get_name());
                }
                return 0;
            }
        }
    }
    else if(menu.button()==Menu::RECOVER) {
        clear();
        WINDOW* sure = newwin(getmaxy(stdscr) / 2 , getmaxx(stdscr) / 2, getmaxy(stdscr) * 1 / 4, getmaxx(stdscr) * 1 / 4);
        refresh();
        box(sure, 0, 0);
        string ok = "Do you want to recover saves for the "+game->get_name()+"?";
        mvwprintw(sure, 1, (getmaxx(sure) - ok.length()) / 2, ok.c_str());
        wattron(sure, A_STANDOUT);
        mvwprintw(sure, getmaxy(sure) - 2, getmaxx(sure) * 1 / 4, "YES");
        wattroff(sure, A_STANDOUT);
        mvwprintw(sure, getmaxy(sure) - 2, getmaxx(sure) * 3 / 4 - 1, "NO");
        bool yes = true;
        char ch;
        while(ch = wgetch(sure)) {
            switch(ch) 
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
                if(yes) {
                    bluise_core::recover(game->get_name());
                }
                return 0;
            }
        }
    }
}

