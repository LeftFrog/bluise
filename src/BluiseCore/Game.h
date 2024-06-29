#pragma once
#include <QPixmap>
#include <string>

using std::string;
class Game {

public:
  enum class var_type { name, workingDirectory, executable, savePath };
  enum Runner { Native,
                GamePortingToolkit };

  inline QString getName() const { return name; }
  inline QString getWorkingDirectory() const { return workingDirectory; }
  inline QString getExecutable() const { return executable; }
  inline QString getSavePath() const { return savePath; }
  inline QString getHeaderName() const { return headerName; }
  inline QString getHeaderPath() const { return headerPath; }
  inline QString getCoverPath() const { return coverPath; }
  inline QString getCoverName() const { return coverName; }
  inline QPixmap getHeader() const { return header; }
  inline QPixmap getCover() const { return cover; }
  inline int getRunner() const { return runner; }

  inline int getReleaseYear() const { return releaseYear; }
  bool isDisabled() const { return disabled; }

  void setName(const QString &n) { name = n; };
  void setWorkingDirectory(const QString &wd);
  void setExecutable(const QString &e);
  void setSavePath(QString sp);
  void setReleaseYear(int year) { releaseYear = year; }
  void setCover(const QString &_coverName);
  void setRunner(const Runner& _runner) { runner = _runner; }

  Game();
  Game(const QString &n, const QString &e, const QString &wd = "",
       const QString &sp = "", const QString &_coverName = "",
       bool _disabled = false);

  void execute() const;

  bool operator<(const Game &other) const;
  bool operator==(const Game &other) const;
  bool operator==(const string &other) const;
  bool operator==(const QString &other) const;

private:
  QString name;
  QString workingDirectory;
  QString executable;
  QString savePath;
  QString headerName;
  QString headerPath;
  QString coverPath;
  QString coverName;
  QPixmap header;
  QPixmap cover;
  Runner runner;
  int releaseYear;
  bool disabled;
};
