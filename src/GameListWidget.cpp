#include "GameListWidget.h"
#include "bluise.h"

GameListWidget::GameListWidget(QWidget *parent) : QWidget(parent) {
  layout = new QGridLayout();
  layout->setAlignment(Qt::AlignTop);
  filters_map["Show unistalled"] = Filter::NotInstalled;
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
  if(checked) {
    filters |= Filter::NotInstalled;// filters_map[filter];
  } else {
    filters &= (filters_map[filter]);
  }
  if(checked) {
    if(Filter::NotInstalled & filters) {
      for(int i = 0; i < bluise_core::games.size(); ++i) {
        if(bluise_core::games[i].isDisabled()) {
          game_widgets.push_back(new GameWidget(&bluise_core::games[i], this));
        }
      }
    }
  } else {
    if(!(Filter::NotInstalled & filters)) {
      for(auto game : game_widgets) {
        qDebug() << game->name() << game->isDisabled();
        if(game->isDisabled()) {
          qDebug() << "NotInstalled";
          game_widgets.remove(game_widgets.indexOf(game));
          delete game;
        }
      }
    }
  }
  sortWidgets("Name");
  qDebug() << filters << game_widgets.size();
  addWidgets();
}
