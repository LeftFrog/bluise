#include "GameScrollArea.h"
#include "GameListWidget.h"

GameScrollArea::GameScrollArea(QWidget *parent) : QScrollArea(parent) {
  GameListWidget* gameListWidget = new GameListWidget(this);
  setWidget(gameListWidget);
  horizontalScrollBar()->setEnabled(false);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  verticalScrollBar()->setEnabled(true);
  resize(1280, 720);
  setMinimumWidth(gameListWidget->sizeHint().width());
  setMinimumHeight(300);
  addWidget = new AddWidget(this);
  addWidget->setGeometry(10, height() - 60, 50, 50);
}

void GameScrollArea::resizeEvent(QResizeEvent * event)
{
  addWidget->setGeometry(10, height() - 60, 50, 50);
  QScrollArea::resizeEvent(event);
}
