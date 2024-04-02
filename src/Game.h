#pragma once
#include <QPixmap>
#include <string>

using std::string;
class Game {

public:
  enum class var_type { name, workingDirectory, executable, savePath };

  inline QString getName() const { return name; }
  inline QString getWorkingDirectory() const { return workingDirectory; }
  inline QString getExecutable() const { return executable; }
  inline QString getSavePath() const { return savePath; }
  inline QString getHeaderName() const { return headerName; }
  inline QString getHeaderPath() const { return headerPath; }
  inline int getReleaseYear() const { return releaseYear; }
  bool isDisabled() const { return disabled; }

  void setName(const QString &n) { name = n; };
  void setWorkingDirectory(const QString &wd);
  void setExecutable(const QString &e);
  void setSavePath(QString sp);
  void setReleaseYear(int year) { releaseYear = year; }

  Game();
  Game(const QString &n, const QString &e, const QString &wd = "",
       const QString &sp = "", const QString &_headerName = "",
       bool _disabled = false);

  void execute() const;

  bool operator<(const Game &other) const;
  bool operator==(const Game &other) const;
  bool operator==(const string &other) const;
  bool operator==(const QString &other) const;

protected:
  QString name;
  QString workingDirectory;
  QString executable;
  QString savePath;
  QString headerName;
  QString headerPath;
  int releaseYear;
  bool disabled;
};
