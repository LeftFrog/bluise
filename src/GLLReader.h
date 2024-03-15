#pragma once
#include <QList>
#include "Game.h"
#include <iostream>

namespace bluise_core {
std::ostream& operator<<(std::ostream& os, QList<Game>& games);
inline string get_var(const string& var_name, std::istream& is);
std::istream& operator>>(std::istream& is, QList<Game>& games);
}
