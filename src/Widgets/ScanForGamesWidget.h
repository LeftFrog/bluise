#pragma once
#include <QWidget>
#include <QProgressBar>
#include <QTextEdit>

class ScanForGamesWidget : public QWidget
{
	Q_OBJECT

public:
  ScanForGamesWidget(QWidget* parent = nullptr);

signals:
  void finished();

public slots:
  void scan();
  void foundGames();

private:
  int filesCount(const QString& path);
  QProgressBar* progress;
  QTextEdit* text;
};