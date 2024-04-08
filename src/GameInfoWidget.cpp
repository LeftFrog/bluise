#include "GameInfoWidget.h"
#include <QtWidgets>
#include "GameEditWidget.h"
#include <QQuickItem>

GameInfoWidget::GameInfoWidget(QWidget *parent) : QQuickWidget(QUrl("./GameInfoWidget.qml"), parent) {
  game = nullptr;
  setFixedHeight(100);
  QQuickItem *row = rootObject()->findChild<QQuickItem*>("column")->findChild<QQuickItem*>("row");
  connect(row->findChild<QQuickItem *>("play"), SIGNAL(playClicked()), this, SLOT(play()));
  connect(row->findChild<QQuickItem *>("settings"), SIGNAL(settingsClicked()), this, SLOT(settings()));

}

void GameInfoWidget::setGame(const QModelIndex& index) {
  game = index.data(Qt::UserRole + 1).value<Game *>();
  rootObject()->setProperty("nameText", game->getName());
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

void GameInfoWidget::resizeEvent(QResizeEvent *event) {
  QQuickWidget::resizeEvent(event);
  rootObject()->setProperty("width", width());
  rootObject()->setProperty("height", height());
}