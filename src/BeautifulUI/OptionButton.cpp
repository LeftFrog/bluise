//
// Created by Leonov Oleksandr on 2024-07-28.
//

#include "OptionButton.h"
#include <QPainter>
#include <QStyleHints>
#include <QGuiApplication>

BeautifulUi::OptionButton::OptionButton(const QString& text, QWidget* parent) : AbstractBeautifulButton(parent), text(text) {
    setMinimumHeight(60);
    setMinimumWidth(200);
}

void BeautifulUi::OptionButton::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    QColor color = palette().color(QPalette::Base);
    if(isDown()) {
        color = QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark ? color.darker(40) : color.lighter(80);
    } else if (hovered) {
        color = QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark ? color.darker(55) : color.lighter(95);
    }

    painter.setBrush(QBrush(color));
    painter.drawRect(rect());

    icon().paint(&painter, QRect(iconMargin, iconMargin, height()-(iconMargin*2), height()-(iconMargin*2)), Qt::AlignCenter, isChecked() ? QIcon::Selected : QIcon::Normal);
}
