//
// Created by Leonov Oleksandr on 8/23/24.
//

#include "IconHandler.h"

#include <QGuiApplication>
#include <QStyleHints>

IconHandler::IconHandler(QObject* parent) : QObject(parent) {
    connect(QGuiApplication::styleHints(), &QStyleHints::colorSchemeChanged, this, &IconHandler::changeColorScheme);
}

QIcon IconHandler::getIcon(int style, int icon) {
    return awesome->icon(style, icon);
}

void IconHandler::initFontAwesome() {
    awesome = new fa::QtAwesome(this);
    awesome->initFontAwesome();
}

void IconHandler::changeColorScheme(Qt::ColorScheme) {
    initFontAwesome();
}
