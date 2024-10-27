//
// Created by Leonov Oleksandr on 10/2/24.
//

#include "Settings.h"

Settings* Settings::instance = nullptr;

Settings* Settings::getInstance(QObject* parent) {
    if(!instance) {
        instance = new Settings(parent);
    }
    return instance;
}

void Settings::setAccessToken(const QString& token) {
    setValue("sync/googleDrive/accessToken", token);
}

QString Settings::accessToken() const {
    return value("sync/googleDrive/accessToken").toString();
}

void Settings::setRefreshToken(const QString& token) {
    setValue("sync/googleDrive/refreshToken", token);
}

QString Settings::refreshToken() const {
    return value("sync/googleDrive/refreshToken").toString();
}

Settings::Settings(QObject* parent) : QSettings(parent) {

}
