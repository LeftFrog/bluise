#include "ScanForGamesWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QtConcurrent>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>

#include "../BluiseCore/bluise.h"
#include "../BluiseCore/Game.h"
#include "../BluiseCore/invalid_path.h"

ScanForGamesWidget::ScanForGamesWidget(QWidget* parent) : QWidget(parent) {
  label = new QLabel("Scanning for games...");
  label->setAlignment(Qt::AlignCenter);
  progress = new QProgressBar();
  progress->setAlignment(Qt::AlignCenter);
  scanner = new GameScanner(this);

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
  scanner->scanDirectory("/Applications");
  // const QString path = "/Applications";
  // progress->setRange(0, 0);
  //
  // QFuture<void> future = QtConcurrent::run([this, path] mutable{
  //   QDirIterator it(path, QStringList() << "*.app", QDir::Files | QDir::Dirs, QDirIterator::Subdirectories);
  //   while (it.hasNext()) {
  //     QSqlQuery query(db);
  //     query.prepare("SELECT game_id FROM game_executables WHERE executable = :executable");
  //     QString file = it.next();
  //     QFileInfo info(file);
  //     query.bindValue(":executable", info.fileName());
  //     if(query.exec()) {
  //       if(query.next()) {
  //         gameMap[query.value(0).toInt()] = info.filePath();
  //       }
  //     }
  //   }
  // });
  // watcher.setFuture(future);
}

void ScanForGamesWidget::closeEvent(QCloseEvent* event) {
  emit closed();
  QWidget::closeEvent(event);
}

void ScanForGamesWidget::foundGames() {
  layout()->removeWidget(progress);
  delete progress;
  label->setText("Found games: ");
  for (auto i : gameMap.values()) {
    text->setAlignment(Qt::AlignLeft);
    if(bluise_core::gameManager.gameExists(i)) {
      gameMap.remove(gameMap.key(i));
    } else {
      text->append(QFileInfo(i).fileName());
    }
  }
  if(text->toPlainText().isEmpty()) {
    text->setPlainText("No new games were found");
    text->setAlignment(Qt::AlignCenter);
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

QString ScanForGamesWidget::getAbsolutePath(const QString& path) {
  QString extendedPath = path;
  if(path.startsWith("~")) {
    extendedPath.replace("~", QDir::homePath());
  }
  return extendedPath;
}

void ScanForGamesWidget::addGames() {
  for (auto id : gameMap.keys()) {
    QString executable = gameMap[id];

    QList<QVariant> values = getValueFromDB("games", "name,release_year", id).toList();
    QString name = values[0].toString();
    int releaseYear = values[1].toInt();

    QString savePath = getValueFromDB("game_save_paths", "save_path", id).toString();
    savePath = getAbsolutePath(savePath);

    QString workingDirectory = executable + "/Contents/";

    try {
      Game game{name, executable, workingDirectory, savePath};
      game.setReleaseYear(releaseYear);
      bluise_core::gameManager.games.push_back(game);
    } catch (invalid_path& err) {
      qDebug() << err.what();
    }
  }
  close();
}

