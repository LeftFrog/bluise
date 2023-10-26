#include "GameListWidget.h"

GameListWidget::GameListWidget(QWidget *parent)
{
    setMinimumSize(QSize((5+260)*3+5*2, (5+145)*3+5*2));
    for(auto game : bluise_core::games) {
        game_widgets.push_back(GameWidget(new QGame(game)));
    }
    QGridLayout *layout = new QGridLayout(this);
    int rows = game_widgets.size()/3;
    for(short i=0; i<game_widgets.size(); i++) {
        layout->addWidget(game_widgets[i], i/3, i%3);
    }
    setLayout(layout);
}