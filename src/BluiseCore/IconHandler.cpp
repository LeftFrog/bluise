//
// Created by Leonov Oleksandr on 8/23/24.
//

#include "IconHandler.h"

IconHandler::IconHandler(QObject* parent) : QObject(parent) {
    // awesome = new fa::QtAwesome(this);
    // awesome->initFontAwesome();
}

QIcon IconHandler::getIcon(int style, int icon) {
    return awesome->icon(style, icon);
}

void IconHandler::initFontAwesome() {
    awesome = new fa::QtAwesome(this);
    awesome->initFontAwesome();
}
