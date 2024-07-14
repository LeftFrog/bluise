#pragma once
#include <QProgressBar>
#include <QTextEdit>
#include <QLabel>
#include "../BluiseCore/GameScanner.h"

class ScanForGamesWidget final : public QWidget
{
	Q_OBJECT

public:
  explicit ScanForGamesWidget(QWidget* parent = nullptr);

signals:
  void closed();
  void gameAdded();

public slots:
  void scan();

protected:
  void closeEvent(QCloseEvent* event) override;

private slots:
  void foundGames();
  void addGames();

private:
  QVariant getValueFromDB(const QString& table, const QString& variable, const int& id);
  QString getAbsolutePath(const QString& path);

  GameScanner* scanner;
  QLabel* label;
  QFutureWatcher<void> watcher;
  QMap<int, QString> gameMap{};
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  QProgressBar* progress;
  QTextEdit* text;
};