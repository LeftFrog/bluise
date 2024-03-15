#include "GameWidget.h"
#include <iostream>

GameWidget::GameWidget(Game* _game, QWidget *parent) : QQuickWidget(QUrl("./GameWidget.qml"), parent), game(_game) {
    resize(sizeHint());
    setMinimumSize(sizeHint());
    
    QQuickItem* root = rootObject();
    QQuickItem* main_rect = root->findChild<QQuickItem*>("MainRect");
    QQuickItem* text = main_rect->findChild<QQuickItem*>("Name");
    text->setProperty("text", game->get_name().c_str());
    main_rect->setProperty("img_source", game->get_header_path());
    connect(main_rect->findChild<QQuickItem*>("play_button"), SIGNAL(playClicked()), SLOT(play()));
}

QSize GameWidget::sizeHint() const {
    return QSize(390, 234);
}

void GameWidget::resizeEvent(QResizeEvent *event)
{
    QQuickItem* root = rootObject();
    root->setProperty("width", event->size().width());
    root->setProperty("height", event->size().height());
    QQuickWidget::resizeEvent(event);
}

void GameWidget::play() {
    game->execute();
}