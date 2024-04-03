#include "GameListWidget.h"
#include "bluise.h"

GameListWidget::GameListWidget(QWidget *parent) : QWidget(parent) {
  layout = new QGridLayout();
  layout->setAlignment(Qt::AlignTop);
  init();
  setLayout(layout);
}

void GameListWidget::init() {
  for (int i = 0; i < bluise_core::games.size(); ++i) {
    // if(bluise_core::games[i].isDisabled()) continue;
    game_widgets.push_back(new GameWidget(&bluise_core::games[i], this));
  }
  addWidgets();
}

void GameListWidget::addWidgets() {
  for (int i = 0; i < game_widgets.size(); ++i) {
    if(Filter::NotInstalled & filters  && game_widgets[i]->isDisabled()) {
    }
    layout->addWidget(game_widgets[i], i / 3, i % 3);
  }
}

void GameListWidget::added() {
  game_widgets.clear();
  init();
  addWidgets();
}

void GameListWidget::sortWidgets(const QString &order) {
  if (order == "Name") {
    std::sort(
        game_widgets.begin(), game_widgets.end(),
        [](GameWidget *a, GameWidget *b) { return a->name() < b->name(); });
  } else if (order == "Release Year") {
    std::sort(game_widgets.begin(), game_widgets.end(),
              [](GameWidget *a, GameWidget *b) {
                return a->releaseYear() < b->releaseYear();
              });
  }
  addWidgets();
}

void GameListWidget::filter(const QString & filter, bool checked) {
  filters = Filter::NotInstalled; 
  for(auto g : game_widgets) {
    if(Filter::NotInstalled & filters && g->isDisabled() && !checked) {
      game_widgets.removeIf([g](GameWidget *gw) { return gw->isDisabled(); });
    }
  }
  addWidgets();
}
