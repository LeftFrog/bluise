//
// Created by Leonov Oleksandr on 2024-07-28.
//

#include "OptionButton.h"
#include <QHBoxLayout>
#include <QPainter>

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

    painter.setBrush(QBrush(palette().color(QPalette::Base)));
    painter.drawRect(rect());
}
