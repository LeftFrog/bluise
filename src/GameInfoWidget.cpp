#include "GameInfoWidget.h"
#include <QtWidgets>
#include "GameEditWidget.h"
#include <QQuickItem>
#include "bluise.h"

GameInfoWidget::GameInfoWidget(QWidget *parent) : QWidget(parent) {
  QPushButton *play = new QPushButton("Play");
  QPushButton *settings_button = new QPushButton();
  QApplication::palette();
  QIcon::setFallbackSearchPaths(QIcon::fallbackSearchPaths() << "../res/");
  settings_button->setIcon(QIcon::fromTheme("go-down")); 

  name = new QLabel();
  name->setAlignment(Qt::AlignLeft);
  QHBoxLayout *layout = new QHBoxLayout();
  layout->addWidget(play);
  layout->addWidget(settings_button);
  game = nullptr;
  setFixedHeight(100);
  menu = new QMenu();
  menu->addAction("play", this, SLOT(play()));
  menu->addAction("settings", this, SLOT(settings()));
  setLayout(layout);
}

void GameInfoWidget::setGame(const QModelIndex& index) {
  game = index.data(Qt::UserRole + 1).value<Game *>();
  if(game == nullptr) {
    return;
  }
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


void GameInfoWidget::popupMenu() {
  menu->exec(QCursor::pos());
}