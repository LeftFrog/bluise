#pragma once
#include <QProgressBar>
#include <QTextEdit>
#include <QSqlDatabase>
#include <QLabel>
#include <QFutureWatcher>

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

  QLabel* label;
  QFutureWatcher<void> watcher;
  QMap<int, QString> gameMap{};
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  QProgressBar* progress;
  QTextEdit* text;
};