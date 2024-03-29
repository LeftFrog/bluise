#include "GameListWidget.h"
#include "bluise.h"

GameListWidget::GameListWidget(QWidget *parent) : QWidget(parent) {
  for (int i = 0; i < bluise_core::games.size(); ++i) {
    // if(bluise_core::games[i].isDisabled()) continue;
    game_widgets.push_back(new GameWidget(&bluise_core::games[i], this));
  }
  layout = new QGridLayout();
  addWidgets();
  setBackgroundRole(QPalette::Base);
  setLayout(layout);
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
  for (int i = 0; i < game_widgets.size(); ++i) {
    layout->addWidget(game_widgets[i], i / 3, i % 3);
  }
}

void GameListWidget::added()
{
  game_widgets.clear();
  init();
  addWidgets();
}