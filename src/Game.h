#pragma once
#include <string>

using namespace std;

class Game
{
    enum exec_type{linux_exe, windows_exe};
    string name;
    string working_directory;
    string executable;
    string save_path;
    exec_type type;
public:
    string get_name() { return name; }
    string get_working_directory() { return working_directory; }
    string get_executable() { return executable; }
    string get_save_path() { return save_path; }
    Game(string n, string wd, string e, string sp);
    void execute();
    bool operator==(Game& other);
    bool operator==(string& other);
};
