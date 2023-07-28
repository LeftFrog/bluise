#include "../command_line/command_processor.cpp"
#include "GameLine.h"

namespace {

vector<GameLine> game_lines;
int maxx, maxy;
WINDOW* bluise;
int current_index = 0;

const char ENTER = 10;
const char RIGHT_ARROW = 67;
const char LEFT_ARROW = 68;
const char UP_ARROW = 65;
const char DOWN_ARROW = 66;

void print_games() {
    for(const auto gl : game_lines) {
        gl.print();
    }
}

const void update_pos() {
    for(int i = 0; i < game_lines.size(); ++i) {
        game_lines[i].update_pos(i+1);
    }
}

const void print_current() {
    print_games();
    wattron(bluise, A_STANDOUT);
    game_lines[current_index].print();
    wattroff(bluise, A_STANDOUT);
    game_lines[current_index].print_menu();
}

void print_bluise() {
    box(bluise, 0, 0);
    mvwprintw(bluise, 0, (maxx - 10)/2, "Bluise");
    refresh();
    wrefresh(bluise);
}

inline void init_game_lines() {
    game_lines.reserve(bluise_core::games.size());
    for(int i = 0; i < games.size(); ++i) {
        game_lines.push_back(GameLine(bluise, &games[i], i+1));
    }
}

void init_ui() {
    initscr();
    noecho();
    curs_set(0);
    maxx = getmaxx(stdscr);
    maxy = getmaxy(stdscr);
    bluise = newwin(maxy - 3, maxx - 2, 2, 2);
    print_bluise();
    init_game_lines();
    print_current();
    wrefresh(bluise);
}

void process_input() {
    nodelay(bluise, true); 
    timeout(100); 

    char ch;
    while((ch = wgetch(bluise))) {
        switch (ch)
        {
        case UP_ARROW:
        case 'w':
            game_lines[current_index].clear_menu();
            if(current_index==0) {
                current_index = game_lines.size() - 1;
            }
            else {
                current_index -= 1; 
            }
            print_current();
            break;
        case DOWN_ARROW:
        case 's':
            game_lines[current_index].clear_menu();
            if(current_index==game_lines.size() - 1) {
                current_index = 0;
            }
            else {
                current_index += 1; 
            }
            print_current();
            break;
        case RIGHT_ARROW:
        case 'd':
            game_lines[current_index].next();
            game_lines[current_index].print_menu();
            break;
        case LEFT_ARROW:
        case 'a':
            game_lines[current_index].previous();
            game_lines[current_index].print_menu();
            break;
        case ENTER:
            if(game_lines[current_index].enter() == 1) {
                string name = game_lines[current_index].name();
                game_lines.erase(game_lines.begin() + current_index);
                bluise_core::delete_game(name);
                bluise_core::saveGLL();
                update_pos();
            }
            current_index = 0;
            clear();
            werase(bluise);
            print_bluise();
            print_current();
            break;
        default:
            break;
        }
    } 
}

void print_ui() {
    init_ui();
    
    process_input();

    getch();
    endwin();
}

}
