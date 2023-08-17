#pragma once
#include <string>
#include <QVector>
#include <Game.h>
#include <iostream>
#include "gll_syntax_error.h"

namespace bluise_core {
ostream& operator<<(ostream& os, QVector<Game>& games);
inline string get_var(const string& var_name, istream& is);
istream& operator>>(istream& is, QVector<Game>& games);
}