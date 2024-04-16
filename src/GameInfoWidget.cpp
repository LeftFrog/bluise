#include "GameInfoWidget.h"
#include "./ui_GameInfoWidget.h"
#include <QtWidgets>
#include "GameEditWidget.h"
#include <QQuickItem>
#include "bluise.h"

GameInfoWidget::GameInfoWidget(QWidget *parent) : QWidget(parent), ui(new Ui::GameInfoWidget) {
  ui->setupUi(this);
  setFixedHeight(100);
  ui->label->setFont(QFont("Arial", 22));
}

GameInfoWidget::~GameInfoWidget() {
  delete ui;
}

void GameInfoWidget::setGame(const QModelIndex& index) {
  game = index.data(Qt::UserRole + 1).value<Game *>();
  if(game == nullptr) {
    return;
  }
  ui->label->setText(game->getName());
  this->show();
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


void GameInfoWidget::popupMenu() {
  menu->exec(QCursor::pos());
}