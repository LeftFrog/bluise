#pragma once
#include <string>
//#include <QIcon>
#include <QPixmap>
//#include "bluise.h"

using std::string;
class Game
{

protected:
    enum exec_type{linux_exe, windows_exe};

    string name;
    string working_directory;
    string executable;
    string save_path;
    QString header_path;
    //QIcon icon;
    
    exec_type type;

public:
    enum class var_type{name, working_directory, executable, save_path};

    inline string get_name() const { return name; }
    inline string get_working_directory() const { return working_directory; }
    inline string get_executable() const { return executable; }
    inline string get_save_path() const { return save_path; }
    //QIcon get_icon() const { return icon; }
    QString get_header_path() const { return header_path; }

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