//
// Created by Leonov Oleksandr on 8/27/24.
//

#include "MenuButton.h"
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>

MenuButton::MenuButton(QWidget* parent) : AbstractBeautifulButton(parent) {

}

MenuButton::MenuButton(QMenu* menu, QWidget* parent) : AbstractBeautifulButton(parent), menu(menu) {

}

MenuButton::MenuButton(const QString& text, QMenu* menu, QWidget* parent) : AbstractBeautifulButton(parent) {
    setText(text);
    this->menu = menu;
}

void MenuButton::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(palette().color(QPalette::Light)));
    painter.drawRoundedRect(rect(), 4, 4);

    mainRect = QRect(0, 0, width()-height()-3, height());
    menuRect = QRect(width()-height(), 0, height(), height());

    painter.setPen(QPen(palette().color(QPalette::Midlight), 1));
    painter.drawLine(width()-height()-1, 5, width()-height()-1, height()-5);

    painter.setPen(QPen(palette().color(QPalette::Text), 1));

    painter.drawText(mainRect, Qt::AlignCenter, text());
    painter.drawText(menuRect, Qt::AlignCenter, "▼");
}

void MenuButton::mousePressEvent(QMouseEvent* event) {
    if (mainRect.contains(event->pos())) {
        click();
    }
    else if (menuRect.contains(event->pos()) && menu) {
        menu->exec(mapToGlobal(QPoint(0, height())));
    }
   AbstractBeautifulButton::mousePressEvent(event);
}
