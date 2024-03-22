#pragma once
#include <string>
#include <QPixmap>

using std::string;
class Game
{

protected:
    enum exec_type{linux_exe, windows_exe};

    QString name;
    QString working_directory;
    QString executable;
    QString save_path;
    QString header_name;
    QString header_path;

    exec_type type;

public:
    enum class var_type{name, working_directory, executable, save_path};

    inline QString get_name() const { return name; }
    inline QString get_working_directory() const { return working_directory; }
    inline QString get_executable() const { return executable; }
    inline QString get_save_path() const { return save_path; }
    QString get_header_name() const { return header_name; }
    QString get_header_path() const { return header_path; }

    void set_name(const QString& n) { name = n; } ;
    void set_working_directory(const QString& wd);
    void set_executable(const QString& e);
    void set_save_path(QString sp);

    Game() {}
    Game(const QString& n, const QString& wd, const QString& e, const QString& sp, const QString& _header_name = "");

    void execute() const;

    bool operator<(const Game& other);
    bool operator==(const Game& other);
    bool operator==(const string& other);
    bool operator==(const QString& other);
};
