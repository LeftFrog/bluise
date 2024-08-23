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

void IconHandler::registerButton(QAbstractButton* button, int icon) {
    icons[button] = icon;
}

void IconHandler::unregisterButton(QAbstractButton* button) {
    icons.remove(button);
}

void IconHandler::changeColorScheme(Qt::ColorScheme) {
    initFontAwesome();
    updateIcons();
}

void IconHandler::updateIcons() {
    for(auto it = icons.begin(); it != icons.end(); ++it) {
        it.key()->setIcon(getIcon(fa::fa_solid, it.value()));
    }
}
