#include "GameListWidget.h"
#include "bluise.h"

// template <typename Iterator, typename Compare> 
// Iterator part(Iterator begin, Iterator end, Compare comp) {
//   auto previous = std::prev(end, 1);
//   auto i = begin;
//   for (auto j = begin; j != previous; ++j) {
//     if (comp(*j, *previous)) {
//       std::swap(*i++, *j);
//     }
//   }
//   std::swap(*i, *previous);
//   return i;
// }

// template <typename Iterator, typename Compare> 
// void sort(Iterator begin, Iterator end, Compare comp) {
//   if (std::distance(begin, end) > 1) {
//     Iterator bound = part(begin, end, comp);
//     sort(begin, bound, comp);
//     sort(bound + 1, end, comp);
//   }
// }

GameListWidget::GameListWidget(QWidget *parent) : QWidget(parent) {
  for (int i = 0; i < bluise_core::games.size(); ++i) {
    game_widgets.push_back(new GameWidget(&bluise_core::games[i], this));
  }
  // sort(game_widgets.begin(), game_widgets.end(), [](const GameWidget *a, const GameWidget *b) { return *a > *b; });
  QGridLayout *layout = new QGridLayout();
  for (int i = 0; i < game_widgets.size(); ++i) {
    layout->addWidget(game_widgets[i], i / 3, i % 3);
  }
  // gameWidgetsProxy = QList<GameWidget *>(game_widgets);
  // const auto lambda = [](const GameWidget &a, const GameWidget &b) { return a > b; };
  // bluise_core::sort(gameWidgetsProxy.begin(), gameWidgetsProxy.end(), lambda);
  // bluise_core::sort(gameWidgetsProxy.begin(), gameWidgetsProxy.end(), lambda);
  // for (int i = 0; i < gameWidgetsProxy.size(); ++i) {
  //   layout->addWidget(gameWidgetsProxy[i], i / 3, i % 3);
  // }
  setLayout(layout);
}