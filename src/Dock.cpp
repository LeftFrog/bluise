#include "Dock.h"
#include "GameAddWidget.h"



Dock::Dock(QWidget * parent) : QQuickWidget(QUrl("Dock.qml"), parent)
{
  QQuickItem *root = this->rootObject();
  connect(root->findChild<QQuickItem *>("addButton"), SIGNAL(addClicked()), SLOT(addGame()));
}

void Dock::addGame()
{
  GameAddWidget *add_widget = new GameAddWidget();
  add_widget->show();
}