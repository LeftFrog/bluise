//
// Created by Leonov Oleksandr on 9/8/24.
//

#include "GoogleDriveManager.h"
#include <QDesktopServices>

GoogleDriveManager::GoogleDriveManager(QObject* parent) : QObject(parent), oauth(), networkManager() {

}

void GoogleDriveManager::authenticate() {
    oauth.setAuthorizationUrl(QUrl("https://accounts.google.com/o/oauth2/auth"));
    oauth.setAccessTokenUrl(QUrl("https://accounts.google.com/o/oauth2/token"));
    oauth.setClientIdentifier(getenv("GOOGLE_CLIENT_ID"));
    oauth.setClientIdentifierSharedKey(getenv("GOOGLE_CLIENT_SECRET"));

    oauth.setScope("https://www.googleapis.com/auth/drive.file");

    connect(&oauth, &QOAuth2AuthorizationCodeFlow::granted, this, [this]() {
qDebug() << "Authorization granted. Token:" << oauth.token();
});

    connect(&oauth, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);

    qDebug() << "Granting access...";

    oauth.grant();
}
