#include "GameInfoWidget.h"
#include <QtWidgets>

GameInfoWidget::GameInfoWidget(QWidget *parent) : QWidget(parent) {
  game = nullptr;
  QHBoxLayout *HBL1 = new QHBoxLayout();
  QHBoxLayout *HBL2 = new QHBoxLayout();
  QVBoxLayout *VBL = new QVBoxLayout();
  QPushButton *button = new QPushButton("Play", this);
  QPushButton *button2 = new QPushButton("Settings", this);
  name = new QLabel(this);
  HBL1->addWidget(name, Qt::AlignVCenter | Qt::AlignLeft);
  VBL->addLayout(HBL1, Qt::AlignVCenter | Qt::AlignLeft);
  HBL2->addWidget(button, Qt::AlignVCenter | Qt::AlignLeft);
  HBL2->addWidget(button2, Qt::AlignVCenter | Qt::AlignLeft);
  VBL->addLayout(HBL2, Qt::AlignVCenter | Qt::AlignLeft);

  setBackgroundRole(QPalette::Midlight);
  setMaximumHeight(140);
  setLayout(VBL);
}

void GameInfoWidget::setGame(const QModelIndex& index) {
  game = index.data(Qt::UserRole + 1).value<Game *>();
  name->setText(game->getName());
  show();
}