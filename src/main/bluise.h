#pragma once
#include <vector>
#include <string>
#include "Game.h"
#include "invalid_path.h"
#include "gll_syntax_error.h"
#include "GLLReader.cpp"

vector<Game> games{};

inline void saveGLL();
inline void readGLL();

inline void add(string name, string working_directory, string executable, string save_path) { games.push_back(Game(name, working_directory, executable, save_path)); }