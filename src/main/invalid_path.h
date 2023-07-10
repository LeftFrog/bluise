#pragma once
#include "bluise_error.h"

class invalid_path : public bluise_error {
public:
    invalid_path(const string& _msg) : bluise_error(_msg) {}
};