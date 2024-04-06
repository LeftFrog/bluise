#include "GameInfoWidget.h"
#include <QtWidgets>
#include "GameEditWidget.h"

GameInfoWidget::GameInfoWidget(QWidget *parent) : QWidget(parent) {
  game = nullptr;
  QHBoxLayout *HBL1 = new QHBoxLayout();
  QHBoxLayout *HBL2 = new QHBoxLayout();
  QVBoxLayout *VBL = new QVBoxLayout();
  QPushButton *play = new QPushButton("Play", this);
  play->resize(100, 50);
  connect(play, &QPushButton::clicked, this, &GameInfoWidget::play);
  QPushButton *settings = new QPushButton("Settings", this);
  connect(settings, &QPushButton::clicked, this, &GameInfoWidget::settings);
  settings->resize(100, 50);
  name = new QLabel(this);
  name->setStyleSheet("font-size: 20px;");
  HBL1->addWidget(name, Qt::AlignVCenter | Qt::AlignLeft);
  VBL->addLayout(HBL1, Qt::AlignVCenter | Qt::AlignLeft);
  HBL2->addWidget(play, Qt::AlignVCenter | Qt::AlignLeft);
  HBL2->addWidget(settings, Qt::AlignVCenter | Qt::AlignLeft);
  VBL->addLayout(HBL2, Qt::AlignVCenter | Qt::AlignLeft);

  setBackgroundRole(QPalette::Midlight);
  setMaximumHeight(110);
  setLayout(VBL);
}

void GameInfoWidget::setGame(const QModelIndex& index) {
  game = index.data(Qt::UserRole + 1).value<Game *>();
  name->setText(game->getName());
  show();
}

void GameInfoWidget::play() {
  if(game->isDisabled()) {
    QMessageBox::critical(this, "Error", "This game is not available.");
  }
  else {
    game->execute();
  }
}

void GameInfoWidget::settings() {
  GameEditWidget *edit_widget = new GameEditWidget(game);
  edit_widget->show();
}