//
// Created by Leonov Oleksandr on 2024-07-28.
//

#include "OptionButton.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QStyleHints>
#include <QGuiApplication>

BeautifulUi::OptionButton::OptionButton(const QString& text, QWidget* parent) : AbstractBeautifulButton(parent){
    this->text = new QLabel(text, this);
    this->text->setStyleSheet("font-weight=bold;");

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(this->text);
    setLayout(layout);
}

void BeautifulUi::OptionButton::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    QColor color = palette().color(QPalette::Base);
    if (hovered) {
        color = QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark ? color.darker(55) : color.lighter(95);
    }

    painter.setBrush(QBrush(color));
    painter.drawRect(rect());
}
