#include "ScanForGamesWidget.h"
#include <QVBoxLayout>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QPushButton>
#include <QtConcurrent>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>

ScanForGamesWidget::ScanForGamesWidget(QWidget* parent) : QWidget(parent) {
  label = new QLabel("Scanning for games...");
  label->setAlignment(Qt::AlignCenter);
  progress = new QProgressBar();
  progress->setAlignment(Qt::AlignCenter);

  text = new QTextEdit();

  db.setDatabaseName("/Users/leftfrog/Projects/bluise/res/games.db");
  if(!db.open()) {
    qDebug() << "Failed to open database";
  }

  connect(&watcher, &QFutureWatcher<void>::finished, this, &ScanForGamesWidget::foundGames);

  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(label);
  layout->addWidget(progress);
  setLayout(layout);
}

void ScanForGamesWidget::scan() {
  const QString path = "/Applications";
  progress->setRange(0, 0);

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
          gameMap[query.value(0).toInt()] = info.filePath();
        }
      }
    }
  });
  watcher.setFuture(future);
}

void ScanForGamesWidget::closeEvent(QCloseEvent* event) {
  emit closed();
  QWidget::closeEvent(event);
}

void ScanForGamesWidget::foundGames() {
  layout()->removeWidget(progress);
  delete progress;
  label->setText("Found games: ");
  if(gameMap.empty()) {
    text->setPlainText("No games found");
    text->setAlignment(Qt::AlignCenter);
  } else {
    for (auto i : gameMap.values()) {
      text->setAlignment(Qt::AlignLeft);
      text->append(QFileInfo(i).fileName());
    }
  }
  text->setReadOnly(true);
  layout()->addWidget(text);

  auto* cancel = new QPushButton("Cancel");
  auto* add = new QPushButton("Add");
  connect(add, &QPushButton::clicked, this, &ScanForGamesWidget::addGames);
  add->setDefault(true);

  connect(cancel, &QPushButton::clicked, this, &ScanForGamesWidget::close);

  auto* HBL = new QHBoxLayout;
  HBL->addWidget(cancel);
  HBL->addWidget(add);
  dynamic_cast<QVBoxLayout*>(layout())->addLayout(HBL);
}

QVariant ScanForGamesWidget::getValueFromDB(const QString& table, const QString& variable, const int& id) {
  QSqlQuery query(db);
  QString idStr = table != "games" ? "game_id" : "id";
  query.prepare(QString("SELECT %1 FROM %2 WHERE %3 = :id").arg(variable).arg(table).arg(idStr));
  query.bindValue(":id", id);

  if (query.exec()) {}
    while (query.next()) {
      QSqlRecord record = query.record();
      QStringList list = variable.split(',');
      qDebug() << list;
      if(list.count()==1) {
        return QVariant(record.value(variable));
      }
      QList<QVariant> values;
      for (auto var : list) {
        values.append(QVariant(record.value(var)));
      }
      return QVariant(values);
    }
  return QVariant();
}

void ScanForGamesWidget::addGames() {
  for (auto id : gameMap.keys()) {
    QString executable = gameMap[id];

    QList<QVariant> values = getValueFromDB("games", "name,release_year", id).toList();
    QString name = values[0].toString();
    int releaseYear = values[1].toInt();

    QString savePath = getValueFromDB("game_save_paths", "save_path", id).toString();

    qDebug() << executable << "\n" << name << releaseYear << "\n" << savePath;
  }
}

