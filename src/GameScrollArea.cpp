#include "GameScrollArea.h"
#include "GameListWidget.h"

GameScrollArea::GameScrollArea(QWidget *parent) : QScrollArea(parent) {
  GameListWidget *gameListWidget = new GameListWidget(this);
  setWidget(gameListWidget);
  horizontalScrollBar()->setEnabled(false);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  verticalScrollBar()->setEnabled(true);
  resize(1280, 720);
  setMinimumWidth(gameListWidget->sizeHint().width());
  setMinimumHeight(300);
}