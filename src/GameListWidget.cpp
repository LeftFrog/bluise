#include "GameListWidget.h"
#include "bluise.h"

GameListWidget::GameListWidget(QWidget *parent) : QWidget(parent)
{
    for(int i = 0; i < bluise_core::games.size(); ++i) {
        game_widgets.push_back(new GameWidget(&bluise_core::games[i], this));
    }
    QGridLayout *layout = new QGridLayout();
    if(game_widgets.size()>=3) {
        for(int i = 0; i < game_widgets.size(); ++i) {
            if(i==3) {
                layout->addWidget(game_widgets[i], 1, 0);
            }
            else {
                layout->addWidget(game_widgets[i], 0, i);
            }
        }
    }
    setLayout(layout);
}