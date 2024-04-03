#include "Dock.h"
#include "GameAddWidget.h"

Dock::Dock(QWidget *parent) : QQuickWidget(QUrl("Dock.qml"), parent) {
  QQuickItem *root = this->rootObject();
  connect(root->findChild<QQuickItem *>("addButton"), SIGNAL(addClicked()),
          SLOT(addGame()));
  connect(root, SIGNAL(checked(QString)), SIGNAL(sort(const QString &)));
  connect(root, SIGNAL(filter(QString)), SIGNAL(filter(const QString &)));
  setFixedHeight(50);
}

void Dock::resizeEvent(QResizeEvent *event) {
  QQuickItem *root = this->rootObject();
  root->setProperty("width", event->size().width());
  root->setProperty("height", event->size().height());
  QQuickWidget::resizeEvent(event);
}

void Dock::addGame() {
  GameAddWidget *add_widget = new GameAddWidget();
  connect(add_widget, &GameAddWidget::added, this, &Dock::added);
  add_widget->show();
}