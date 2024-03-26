#include "AddWidget.h"
#include "GameAddWidget.h"



AddWidget::AddWidget(QWidget * parent) : QQuickWidget(QUrl("./AddWidget.qml"), parent)
{
  resize(sizeHint());
  setMinimumSize(sizeHint());
  // setFixedSize(sizeHint());

  QQuickItem * root = rootObject();
  QQuickItem * main_rect = root->findChild<QQuickItem *>("mainRect");
  
  connect(root->findChild<QQuickItem *>("addButton"), SIGNAL(addClicked()), SLOT(add()));
}

void AddWidget::resizeEvent(QResizeEvent * event)
{
  QQuickItem * root = rootObject();
  root->setProperty("width", event->size().width());
  root->setProperty("height", event->size().height());
  QQuickWidget::resizeEvent(event);
}

void AddWidget::add()
{
  GameAddWidget * add_widget = new GameAddWidget();
  add_widget->show();
}