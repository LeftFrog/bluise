#pragma once
#include <string>

using namespace std;

class Game
{
    enum exec_type{ linux_exe, windows_exe};
    string name;
    string working_directory;
    string executable;
    string save_path;
    exec_type type;
public:
    Game(string n, string wd, string e, string sp);
    void execute();
    bool operator==(Game& other);
    bool operator==(string& other);
};
