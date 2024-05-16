#pragma once
#include <string>
using std::string;

class bluise_error {
private:
  string msg;

public:
  bluise_error(const string &_msg) : msg(_msg) {}
  string what() const { return msg; }
};