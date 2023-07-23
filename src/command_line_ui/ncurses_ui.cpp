#include "../command_line/command_processor.cpp"
#include "GameLine.h"

namespace {

vector<GameLine> game_lines;

void print_games() {
    for(int i = 0; i < game_lines.size(); ++i) {
        game_lines[i].print();
    }
}

void print_ui() {
    initscr();
    noecho();
    curs_set(0);

    int maxx = getmaxx(stdscr);
    int maxy = getmaxy(stdscr);

    WINDOW* bluise = newwin(maxy - 3, maxx - 2, 2, 2);
    refresh();

    box(bluise, 0, 0);

    mvwprintw(bluise, 0, (maxx - 7)/2 , "Bluise");
    mvwprintw(bluise, 0, 1, "Add");

    for(int i = 0; i < games.size(); ++i) {
        game_lines.push_back(GameLine(bluise, &games[i], i+1, 2));
    }

    int current_index = 0;

    print_games();
    wattron(bluise, A_STANDOUT);
    game_lines[current_index].print();
    wattroff(bluise, A_STANDOUT);
    game_lines[current_index].print_menu();

    wrefresh(bluise);
    char ch;
    while((ch = wgetch(bluise))) {
        switch (ch)
        {
        case 'x':
            wattron(bluise, A_STANDOUT);
            mvwprintw(bluise, 0, 1, "Add");
            wattroff(bluise, A_STANDOUT);
            break;
        case 65:
        case 'w':
            game_lines[current_index].clear_menu();
            if(current_index==0) {
                current_index = game_lines.size() - 1;
            }
            else {
                current_index -= 1; 
            }
            print_games();
            wattron(bluise, A_STANDOUT);
            game_lines[current_index].print();
            wattroff(bluise, A_STANDOUT);
            game_lines[current_index].print_menu();
            break;
        case 66:
        case 's':
            game_lines[current_index].clear_menu();
            if(current_index==game_lines.size() - 1) {
                current_index = 0;
            }
            else {
                current_index += 1; 
            }
            print_games();
            wattron(bluise, A_STANDOUT);
            game_lines[current_index].print();
            wattroff(bluise, A_STANDOUT);
            game_lines[current_index].print_menu();
            break;
        case 67:
        case 'd':
            game_lines[current_index].next();
            game_lines[current_index].print_menu();
            break;
        case 68:
        case 'a':
            game_lines[current_index].previous();
            game_lines[current_index].print_menu();
            break;
        default:
            mvwprintw(bluise, 0, 1, "Add");
            break;
        case 10:
            game_lines[current_index].enter();
        }
    }  

    getch();
    endwin();
}

}
