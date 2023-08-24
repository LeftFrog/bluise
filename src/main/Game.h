#pragma once
#include <string>

using namespace std;

class Game
{
protected:
    enum exec_type{linux_exe, windows_exe};

    string name;
    string working_directory;
    string executable;
    string save_path;
    
    exec_type type;

public:
    inline string get_name() const { return name; }
    inline string get_working_directory() const { return working_directory; }
    inline string get_executable() const { return executable; }
    inline string get_save_path() const { return save_path; }

    void set_name(const string& n) { name = n; } ;
    void set_working_directory(const string& wd);
    void set_executable(const string& e);
    void set_save_path(string sp);

    Game() {}
    Game(const string& n, const string& wd, const string& e, const string& sp);

    void execute() const;

    bool operator<(const Game& other);
    bool operator==(const Game& other);
    bool operator==(const string& other);
};
