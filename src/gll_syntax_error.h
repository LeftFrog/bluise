#pragma once
#include "bluise_error.h"

class gll_syntax_error : public bluise_error {
public:
    gll_syntax_error(const string& _msg) : bluise_error(_msg) {}
};