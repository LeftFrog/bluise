#pragma once
#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <map>
#include "../main/bluise.h"

namespace bluise_command_line {
ostream& operator<<(ostream& os, map<string, string>& al);
istream& operator>>(istream& is, map<string, string>& al);
inline string get_game_var(const string& var_name);
void print_game_vector();
void back(const string& name);
void recover(const string& name);
void add_game();
void print_help();
void delete_game(const string& name);
void show_game_info(const vector<Game>::iterator& game);
void show_info(const string& name);
void run_game(const string& name);
inline bool sure_change(const string& var, const string& val);
void edit_game(string name);
inline void load_aliases();
inline void save_aliases();
void create_alias(const string& alias, const string& name);
const string alias_of(const string& alias);
void delete_alias(const string& alias);
void process_command_line(int& argc, char** argv);
}