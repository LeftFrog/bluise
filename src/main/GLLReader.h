#pragma once
#include <string>
#include <vector>
#include <Game.h>
#include <iostream>
#include "gll_syntax_error.h"

namespace bluise_core {
ostream& operator<<(ostream& os, vector<Game>& games);
inline string get_var(const string& var_name, istream& is);
istream& operator>>(istream& is, vector<Game>& games);
}