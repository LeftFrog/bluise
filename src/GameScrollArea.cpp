#include "GameScrollArea.h"
#include "GameListWidget.h"

GameScrollArea::GameScrollArea(QWidget *parent) : QScrollArea(parent) {
  GameListWidget* gameListWidget = new GameListWidget(this);
  connect(this, &GameScrollArea::added, gameListWidget, &GameListWidget::added);
  setWidget(gameListWidget);

  horizontalScrollBar()->setEnabled(false);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  verticalScrollBar()->setEnabled(true);

  resize(gameListWidget->sizeHint().width(), 720);
  setMinimumWidth(gameListWidget->sizeHint().width());
  setMinimumHeight(300);

  setBackgroundRole(QPalette::Base);
}

void GameScrollArea::resizeEvent(QResizeEvent * event)
{
  QScrollArea::resizeEvent(event);
}
