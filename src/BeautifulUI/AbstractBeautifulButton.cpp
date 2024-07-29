//
// Created by Leonov Oleksandr on 2024-07-29.
//

#include "AbstractBeautifulButton.h"
#include <QApplication>
#include <QEnterEvent>

BeautifulUi::AbstractBeautifulButton::AbstractBeautifulButton(QWidget* parent) : QAbstractButton(parent) {
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover, true);
}

void BeautifulUi::AbstractBeautifulButton::enterEvent(QEnterEvent* event) {
    if (group()) {
        QApplication::sendEvent(parent(), event);
        return;
    }
    hovered = true;
    update();
    QAbstractButton::enterEvent(event);
}

void BeautifulUi::AbstractBeautifulButton::leaveEvent(QEvent* event) {
    if (group()) {
        return;
    }
    hovered = false;
    update();
    QAbstractButton::leaveEvent(event);
}