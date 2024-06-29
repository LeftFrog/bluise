#include "ScanForGamesWidget.h"
#include <QProgressBar>
#include <QLabel>
#include <QVBoxLayout>

ScanForGamesWidget::ScanForGamesWidget(QWidget* parent) : QWidget(parent) {
  QProgressBar* progress = new QProgressBar();
  progress->setRange(0, 100);
  progress->setValue(30);
  progress->setTextVisible(true);

  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(progress);
  setLayout(layout);
}



