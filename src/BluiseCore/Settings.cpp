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

void Settings::setAccessToken(const QString& token) {
    setValue("sync/googleDrive/accessToken", token);
}

QString Settings::accessToken() const {
    return value("sync/googleDrive/accessToken").toString();
}

Settings::Settings(QObject* parent) : QSettings(parent) {

}
