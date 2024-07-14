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
    progress->setRange(0, 0);
    progress->setAlignment(Qt::AlignCenter);

    scanner = new GameScanner(this);

    text = new QTextEdit();

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(progress);
    setLayout(layout);
}

void ScanForGamesWidget::scan() {
    scanner->scanDirectory("/Applications");
}

void ScanForGamesWidget::closeEvent(QCloseEvent* event) {
  emit closed();
  QWidget::closeEvent(event);
}

void ScanForGamesWidget::gamesFound() {
  layout()->removeWidget(progress);
  delete progress;
  label->setText("Found games: ");

  text->setReadOnly(true);
  layout()->addWidget(text);

  auto* cancel = new QPushButton("Cancel");
  auto* add = new QPushButton("Add");
  add->setDefault(true);

  connect(cancel, &QPushButton::clicked, this, &ScanForGamesWidget::close);

  auto* HBL = new QHBoxLayout;
  HBL->addWidget(cancel);
  HBL->addWidget(add);
  dynamic_cast<QVBoxLayout*>(layout())->addLayout(HBL);
}

