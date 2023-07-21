#pragma once
#include <vector>
#include <string>
#include "Game.h"
#include "invalid_path.h"
#include "gll_syntax_error.h"
#include "GLLReader.cpp"
#include <filesystem>

namespace fs = std::filesystem;

namespace bluise_core {
vector<Game> games{};
const string HOME = getenv("HOME");

inline void saveGLL();
inline void readGLL();

void back(const string& name);
void recover(const string& name);
void edit(const string& var, const string& val, const string& name);
void add(const string& name, const string& working_directory, const string& executable, const string& save_path);
void run(const string& name);
void delete_game(const string& name);
}