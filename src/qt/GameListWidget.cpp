#include "GameListWidget.h"

GameListWidget::GameListWidget(QWidget *parent)
{
    QGridLayout *layout = new QGridLayout();
    for(auto game : bluise_core::games) {
        game_widgets.push_back(new GameWidget(new QGame(game)));
    }
    for(int i = 0; i < game_widgets.size(); i++) {
        layout->addWidget(game_widgets[i], 0, i);
    }
    setLayout(layout);
}