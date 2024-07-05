#include "ScanForGamesWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QtConcurrent>

ScanForGamesWidget::ScanForGamesWidget(QWidget* parent) : QWidget(parent) {
  QLabel* label = new QLabel("Scanning for games...");
  label->setAlignment(Qt::AlignCenter);
  progress = new QProgressBar();
  progress->setAlignment(Qt::AlignCenter);
  progress->setRange(0, 100);
  progress->setValue(0);

  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(label);
  layout->addWidget(progress);
  setLayout(layout);

  connect(this, &ScanForGamesWidget::finished, this, &ScanForGamesWidget::foundGames);
}

void ScanForGamesWidget::scan() {
  const QString path = "/Applications";

  progress->setRange(0, 0);

  QtConcurrent::run([this, path]{
    QDirIterator it(path, QStringList() << "*.app", QDir::Files | QDir::Dirs, QDirIterator::Subdirectories);

    int count = 0;
    while (it.hasNext()) {
      QString file = it.next();
      QFileInfo info(file);
      if(info.fileName().endsWith(".app"))
        qDebug() << file;

      QMetaObject::invokeMethod(this, [this, count]{
        progress->setValue(count);
      }, Qt::QueuedConnection);
      count++;
    }
    qDebug() << progress->value();
    emit finished();
  });
}

int ScanForGamesWidget::filesCount(const QString& path) {
  int count = 0;
  QtConcurrent::run([this, path, count] mutable {
    QDirIterator it(path, QStringList() << "*.app", QDir::Files | QDir::Dirs, QDirIterator::Subdirectories);
    while (it.hasNext()) {
      it.next();
      count++;
    }
  });
  return count;
}

void ScanForGamesWidget::foundGames() {
  layout()->removeWidget(progress);
  delete progress;
  text = new QTextEdit();
  text->setPlainText("No games found");
  text->setAlignment(Qt::AlignCenter);
  text->setReadOnly(true);
  layout()->addWidget(text);
}