#include "GameWidget.h"
#include "GameAddWidget.h"
#include "GameEditWidget.h"


GameWidget::GameWidget(Game *_game, QWidget *parent)
    : QQuickWidget(QUrl("./GameWidget.qml"), parent), game(_game) {
  resize(sizeHint());
  setMinimumSize(sizeHint());
  setFixedSize(sizeHint());

  QQuickItem *root = rootObject();
  QQuickItem *main_rect = root->findChild<QQuickItem *>("MainRect");
  QQuickItem *text = main_rect->findChild<QQuickItem *>("Name");
  text->setProperty("text", game->get_name());
  main_rect->setProperty("img_source", game->get_header_path());
  connect(main_rect->findChild<QQuickItem *>("edit_button"),
          SIGNAL(editClicked()), SLOT(edit()));
  connect(main_rect->findChild<QQuickItem *>("play_button"),
          SIGNAL(playClicked()), SLOT(play()));
}

QSize GameWidget::sizeHint() const { return QSize(390, 234); }

bool GameWidget::operator>(const GameWidget & other) const
{
  return game->get_name() > other.game->get_name();
}

void GameWidget::resizeEvent(QResizeEvent *event) {
  QQuickItem *root = rootObject();
  root->setProperty("width", event->size().width());
  root->setProperty("height", event->size().height());
  QQuickWidget::resizeEvent(event);
}

void GameWidget::edit() {
  GameEditWidget *edit_widget = new GameEditWidget(game);
  edit_widget->show();
  connect(edit_widget, SIGNAL(repaint()), SLOT(repaintSlot()));
}

void GameWidget::play() { game->execute(); }

void GameWidget::repaintSlot() {
  QQuickItem *root = rootObject();
  QQuickItem *main_rect = root->findChild<QQuickItem *>("MainRect");
  QQuickItem *text = main_rect->findChild<QQuickItem *>("Name");
  text->setProperty("text", game->get_name());
  update();
}
