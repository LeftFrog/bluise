#pragma once
#include <QPixmap>
#include <string>


using std::string;
class Game {

public:
  enum class var_type { name, working_directory, executable, save_path };

  inline QString get_name() const { return name; }
  inline QString get_working_directory() const { return working_directory; }
  inline QString get_executable() const { return executable; }
  inline QString get_save_path() const { return save_path; }
  inline QString get_header_name() const { return header_name; }
  inline QString get_header_path() const { return header_path; }
  inline int getReleaseYear() const { return release_year; }
  bool isDisabled() const { return disabled; }

  void set_name(const QString &n) { name = n; };
  void set_working_directory(const QString &wd);
  void set_executable(const QString &e);
  void set_save_path(QString sp);
  void setReleaseYear(int year) { release_year = year; }

  Game();
  Game(const QString &n, const QString &wd, const QString &e, const QString &sp,
       const QString &_header_name = "", bool _disabled = false);

  void execute() const;

  bool operator<(const Game &other) const;
  bool operator==(const Game &other) const;
  bool operator==(const string &other) const;
  bool operator==(const QString &other) const;

protected:
  QString name;
  QString working_directory;
  QString executable;
  QString save_path;
  QString header_name;
  QString header_path;
  int release_year;
  bool disabled;
};
