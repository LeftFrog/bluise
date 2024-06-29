#pragma once
#include <QWidget>
#include <QProgressBar>

class ScanForGamesWidget : public QWidget
{
	Q_OBJECT

public:
  ScanForGamesWidget(QWidget* parent = nullptr);

public slots:
  void scan();

private:
  QProgressBar* progress;
};