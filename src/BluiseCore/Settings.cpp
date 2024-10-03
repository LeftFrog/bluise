//
// Created by Leonov Oleksandr on 10/2/24.
//

#include "Settings.h"

Settings* Settings::instance = nullptr;

Settings* Settings::getInstance() {
    if(!instance) {
        instance = new Settings();
    }
    return instance;
}

Settings::Settings(QObject* parent) : QSettings(parent) {

}
