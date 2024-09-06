//
// Created by Leonov Oleksandr on 8/27/24.
//

#include "MenuButton.h"
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QStyleHints>

MenuButton::MenuButton(QWidget* parent) : AbstractBeautifulButton(parent) {

}

MenuButton::MenuButton(QMenu* menu, QWidget* parent) : AbstractBeautifulButton(parent), menu(menu) {
    setMenu(menu);
}

MenuButton::MenuButton(const QString& text, QMenu* menu, QWidget* parent) : AbstractBeautifulButton(parent) {
    setText(text);
    setMenu(menu);
}

void MenuButton::setMenu(QMenu* menu) {
    this->menu = menu;
    connect(menu, &QMenu::aboutToHide, this, &MenuButton::hideMenu);
}

void MenuButton::paintDownButtons(QPainter& painter) {
    QColor color = QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark ? palette().color(QPalette::Light).darker(50) : palette().color(QPalette::Light).lighter(80);
    painter.setBrush(color);
    if(isMenuDown) {
        painter.drawRect(menuRect);
    } else {
        painter.drawRect(mainRect);
    }
}

void MenuButton::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QPainterPath path;
    path.addRoundedRect(rect(), 4, 4);
    painter.setClipPath(path);

    painter.setBrush(QBrush(palette().color(QPalette::Light)));
    painter.drawRect(rect());

    mainRect = QRect(0, 0, width()-height()-2, height());
    menuRect = QRect(width()-height(), 0, height(), height());

    if (isDown()) {
        paintDownButtons(painter);
    }

    QColor color = QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark ? palette().color(QPalette::Midlight).darker(70) : palette().color(QPalette::Light).lighter(80);
    painter.setPen(QPen(color, 1));
    painter.drawLine(width()-height()-1, 5, width()-height()-1, height()-5);

    painter.setPen(QPen(palette().color(QPalette::Text), 1));

    painter.drawText(mainRect, Qt::AlignCenter, text());
    painter.drawText(menuRect, Qt::AlignCenter, "▼");
}

void MenuButton::mousePressEvent(QMouseEvent* event) {
    if (mainRect.contains(event->pos())) {
        isMenuDown = false;
        setDown(true);
        repaint();
        click();
    }
    else if (menuRect.contains(event->pos())) {
        isMenuDown = true;
        setDown(true);
        repaint();
        menu->exec(mapToGlobal(rect().bottomRight()));
    } else {
        setDown(false);
    }
}

void MenuButton::hideMenu() {
    setDown(false);
    isMenuDown = false;
}
