#include "GameListWidget.h"
#include "bluise.h"

GameListWidget::GameListWidget(QWidget *parent)
{
    for(int i = 0; i < bluise_core::games.size(); ++i) {
        game_widgets.push_back(new GameWidget(&bluise_core::games[i], this));
    }
    QGridLayout *layout = new QGridLayout();
    for(int i = 0; i < game_widgets.size(); ++i) {
        layout->addWidget(game_widgets[i], 0, i);
    }
    resize(1280, 300);
    setLayout(layout);
}