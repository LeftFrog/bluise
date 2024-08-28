//
// Created by Leonov Oleksandr on 8/27/24.
//

#include "MenuButton.h"
#include <QPainter>

MenuButton::MenuButton(QWidget* parent) : AbstractBeautifulButton(parent) {

}

MenuButton::MenuButton(QMenu* menu, QWidget* parent) : AbstractBeautifulButton(parent), menu(menu) {

}

void MenuButton::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(palette().color(QPalette::Light)));
    painter.drawRoundedRect(rect(), 4, 4);

    painter.setPen(QPen(palette().color(QPalette::Midlight), 1));
    painter.drawLine(width()-height()-1, 5, width()-height()-1, height()-5);
}
