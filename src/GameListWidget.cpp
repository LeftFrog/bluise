#include "GameListWidget.h"
#include "bluise.h"

GameListWidget::GameListWidget(QWidget *parent) : QWidget(parent) {
  init();
}

void GameListWidget::init()
{
  for (int i = 0; i < bluise_core::games.size(); ++i) {
    // if(bluise_core::games[i].isDisabled()) continue;
    game_widgets.push_back(new GameWidget(&bluise_core::games[i], this));
  }
  addWidgets();
}

void GameListWidget::addWidgets() {
  layout = new QGridLayout();
  for (int i = 0; i < game_widgets.size(); ++i) {
    layout->addWidget(game_widgets[i], i / 3, i % 3);
  }
  setLayout(layout);
}

void GameListWidget::added()
{
  game_widgets.clear();
  init();
  addWidgets();
}