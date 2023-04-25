#pragma once

#include <string>
using std::string;

class invalid_path {
    string message;
public:
    invalid_path(string msg) : message(msg) {}
    string what() const {return message;}
};