#include "GameLine.h"

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

void GameLine::enter(WINDOW* subwin)
{
    mvwprintw(subwin, 2, 4, "HELLP");
}
