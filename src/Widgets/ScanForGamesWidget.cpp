#include "ScanForGamesWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QtConcurrent>
#include <QSqlQuery>
#include <QFutureWatcher>

ScanForGamesWidget::ScanForGamesWidget(QWidget* parent) : QWidget(parent) {
  QLabel* label = new QLabel("Scanning for games...");
  label->setAlignment(Qt::AlignCenter);
  progress = new QProgressBar();
  progress->setAlignment(Qt::AlignCenter);

  db.setDatabaseName("/Users/leftfrog/Projects/bluise/res/games.db");
  if(!db.open()) {
    qDebug() << "Failed to open database";
  }

  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(label);
  layout->addWidget(progress);
  setLayout(layout);
}

void ScanForGamesWidget::scan() {
  const QString path = "/Applications";
  progress->setRange(0, 0);
  QFutureWatcher<void> watcher;

  connect(&watcher, &QFutureWatcher<void>::finished, this, &ScanForGamesWidget::foundGames);

  QFuture<void> future = QtConcurrent::run([this, path] mutable{
    QDirIterator it(path, QStringList() << "*.app", QDir::Files | QDir::Dirs, QDirIterator::Subdirectories);
    while (it.hasNext()) {
      QSqlQuery query(db);
      query.prepare("SELECT game_id FROM game_executables WHERE executable = :executable");
      QString file = it.next();
      QFileInfo info(file);
      query.bindValue(":executable", info.fileName());
      if(query.exec()) {
        if(query.next()) {
          game_ids.append(query.value(0).toInt());
          qDebug() << "lol";
        }
      }
    }
    qDebug() << "hu";
  });
  watcher.setFuture(future);
}

void ScanForGamesWidget::foundGames() {
  layout()->removeWidget(progress);
  delete progress;
  text = new QTextEdit();
  if(game_ids.empty()) {
    text->setPlainText("No games found");
    text->setAlignment(Qt::AlignCenter);
  } else {
    for (auto i : game_ids) {
      text->setAlignment(Qt::AlignLeft);
      QSqlQuery query(QString("SELECT name FROM games WHERE id = %1").arg(i), db);
      if (query.exec()) {
        if (query.next()) {
          text->append(query.value(0).toString());
        }
      }
    }
  }
  text->setReadOnly(true);
  layout()->addWidget(text);
}