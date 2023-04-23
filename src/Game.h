#pragma once
#include <string>

using namespace std;

struct Game
{
    Game(string, string, string, string);
    string name;
    string working_directory;
    string executable;
    string save_path;
    bool operator==(Game& other);
    bool operator==(string& other);
};
