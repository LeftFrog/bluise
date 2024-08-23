//
// Created by Leonov Oleksandr on 2024-07-28.
//

#include "OptionButton.h"
#include <QStyleHints>
#include <QGuiApplication>

#include "../BluiseCore/bluise.h"

BeautifulUi::OptionButton::OptionButton(const QString& text, const QString& description, QWidget* parent) : AbstractBeautifulButton(parent), text(text), description(description) {
    setFixedHeight(60);
    QFontMetrics metrics(font());
    boldFont = font();
    boldFont.setBold(true);
    boldFont.setPixelSize(16);
    QFontMetrics metricsBold(boldFont);
    setMinimumWidth(std::max(metrics.boundingRect(description).width(), metricsBold.boundingRect(text).width())+height()*1.5);
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
    iconHandler.getIcon(fa::fa_solid, fa::fa_chevron_right).paint(&painter, QRect(width()-height()+iconMargin, iconMargin, height()-iconMargin, height()-(iconMargin*2)), Qt::AlignCenter, isChecked() ? QIcon::Selected : QIcon::Normal);

    painter.setPen(QPen(QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark ? Qt::white : Qt::black));
    painter.setBrush(Qt::NoBrush);

    painter.setFont(boldFont);
    painter.drawText(QRect(height(), 0, width()-height(), height()/2), Qt::AlignBottom, text);

    painter.setFont(this->font());
    painter.drawText(QRect(height(), height()/2, width()-height(), height()/2), Qt::AlignTop, description);
}
