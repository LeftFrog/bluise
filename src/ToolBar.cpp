#include "ToolBar.h"
#include <QQuickItem>

ToolBar::ToolBar(QWidget *parent) : QQuickWidget(QUrl("./ToolBar.qml"), parent) {
  setFixedHeight(45);
  rootObject()->setProperty("width", width());
  rootObject()->setProperty("height", height());
}

void ToolBar::resizeEvent(QResizeEvent *event) {
  rootObject()->setProperty("width", width());
  QQuickWidget::resizeEvent(event);
}