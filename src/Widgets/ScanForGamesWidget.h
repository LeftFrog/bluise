#pragma once
#include <QList>
#include <QProgressBar>
#include <QTextEdit>
#include <QSqlDatabase>

class ScanForGamesWidget final : public QWidget
{
	Q_OBJECT

public:
  explicit ScanForGamesWidget(QWidget* parent = nullptr);

public slots:
  void scan();
  void foundGames();

private:
  QList<int> game_ids{};
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  QProgressBar* progress;
  QTextEdit* text;
};