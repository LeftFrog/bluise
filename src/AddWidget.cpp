#include "AddWidget.h"



AddWidget::AddWidget(QWidget * parent) : QQuickWidget(QUrl("./AddWidget.qml"), parent)
{
    resize(sizeHint());
    setMinimumSize(sizeHint());
    // setFixedSize(sizeHint());

    // QQuickItem * root = rootObject();
    // connect(root->findChild<QQuickItem *>("add_button"), SIGNAL(addClicked()), SLOT(add()));
}

void AddWidget::resizeEvent(QResizeEvent * event)
{
    QQuickItem * root = rootObject();
    root->setProperty("width", event->size().width());
    root->setProperty("height", event->size().height());
    QQuickWidget::resizeEvent(event);
}