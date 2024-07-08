#pragma once
#include <QList>
#include <QProgressBar>
#include <QTextEdit>
#include <QSqlDatabase>
#include <QFutureWatcher>

class ScanForGamesWidget final : public QWidget
{
	Q_OBJECT

public:
  explicit ScanForGamesWidget(QWidget* parent = nullptr);

public slots:
  void scan();
  void foundGames();

private:
  void doSomething();
  QFutureWatcher<void> watcher;
  QList<int> game_ids{};
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  QProgressBar* progress;
  QTextEdit* text;
};