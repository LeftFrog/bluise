#pragma once
#include <QProgressBar>
#include <QTextEdit>
#include <QSqlDatabase>
#include <QFutureWatcher>

class ScanForGamesWidget final : public QWidget
{
	Q_OBJECT

public:
  explicit ScanForGamesWidget(QWidget* parent = nullptr);

signals:
  void closed();

public slots:
  void scan();

protected:
  void closeEvent(QCloseEvent* event) override;

private slots:
  void foundGames();

private:
  QFutureWatcher<void> watcher;
  QList<int> game_ids{};
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  QProgressBar* progress;
  QTextEdit* text;
};