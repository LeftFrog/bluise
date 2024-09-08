//
// Created by Leonov Oleksandr on 9/8/24.
//

#include "GoogleDriveManager.h"
#include <QDesktopServices>
#include <QFile>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QOAuthHttpServerReplyHandler>

GoogleDriveManager::GoogleDriveManager(QObject* parent) : QObject(parent), oauth(), networkManager() {
    clientId = getenv("GOOGLE_CLIENT_ID");
    clientSecret = getenv("GOOGLE_CLIENT_SECRET");

    if (clientId.isEmpty() || clientSecret.isEmpty()) {
        qDebug() << "Client ID or Client Secret is not set!";
        return;
    }

    // Set up OAuth authorization and token URLs
    oauth.setAuthorizationUrl(QUrl("https://accounts.google.com/o/oauth2/auth"));
    oauth.setAccessTokenUrl(QUrl("https://oauth2.googleapis.com/token"));

    // Set OAuth client credentials
    oauth.setClientIdentifier(clientId);
    oauth.setClientIdentifierSharedKey(clientSecret);

    // Set redirect URI and scope
    oauth.setScope("https://www.googleapis.com/auth/drive.file");

    // Initialize the reply handler before connecting signals
    QOAuthHttpServerReplyHandler* replyHandler = new QOAuthHttpServerReplyHandler(8080, this);
    oauth.setReplyHandler(replyHandler);

    // Connect OAuth to browser for authorization
    connect(&oauth, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);

    // Handle OAuth errors
    connect(&oauth, &QOAuth2AuthorizationCodeFlow::error, this, [](const QString &error) {
        qDebug() << "OAuth error occurred: " << error;
    });

    // Handle successful token granting
    connect(&oauth, &QOAuth2AuthorizationCodeFlow::granted, this, [this]() {
        qDebug() << "Access token granted.";
        QString token = oauth.token();
        if (token.isEmpty()) {
            qDebug() << "Access token is empty.";
        } else {
            qDebug() << "Access Token: " << token;
            // You can now use the token to make Google Drive API requests
        }
    });
}

void GoogleDriveManager::uploadFile(const QString& localFilePath, const QString& remoteFilePath) {
    QFile* file = new QFile(localFilePath);

    if(!file->open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file";
        return;
    }

    QUrl url("https://www.googleapis.com/upload/drive/v3/files?uploadType=media");
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + oauth.token().toUtf8());

    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"" + remoteFilePath + "\""));
    filePart.setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(filePart);

    QNetworkReply* reply = networkManager.post(request, multiPart);
    multiPart->setParent(reply);

    connect(reply, &QNetworkReply::finished, [reply, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "File uploaded";
        } else {
            qDebug() << "Error uploading file: " << reply->errorString();
        }
        reply->deleteLater();
    });
}

void GoogleDriveManager::authenticate() {
    oauth.grant();
}
