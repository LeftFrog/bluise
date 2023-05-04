#pragma once

#include <string>
using std::string;

class gll_syntax_error {
    string message;
public:
    gll_syntax_error(string msg) : message(msg) {}
    string what() const { return message; }
};