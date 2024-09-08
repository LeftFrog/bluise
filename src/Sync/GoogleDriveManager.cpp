//
// Created by Leonov Oleksandr on 9/8/24.
//

#include "GoogleDriveManager.h"
#include <QDesktopServices>
#include <QFileInfo>
#include <QHttpMultiPart>
#include <QMimeDatabase>
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

void GoogleDriveManager::uploadFile(const QString& localFilePath) {
    QFile* file = new QFile(localFilePath);
    if(!file->open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file";
        return;
    }
    QMimeType mimeType = QMimeDatabase().mimeTypeForFile(localFilePath);

    QUrl url("https://www.googleapis.com/upload/drive/v3/files?uploadType=resumable");
    QNetworkRequest request(url);

    QString token = oauth.token();
    if(token.isEmpty()) {
        qDebug() << "Access token is empty.";
        return;
    }

    request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=UTF-8");
    request.setRawHeader("X-Upload-Content-Type", mimeType.name().toUtf8());
    request.setRawHeader("X-Upload-Content-Length", QByteArray::number(file->size()));

    QByteArray metaData = R"({
        "name": ")" + QFileInfo(*file).fileName().toUtf8() + R"(",
        "mimeType": ")" + mimeType.name().toUtf8() + R"("
    })";

    QNetworkReply* reply = networkManager.post(request, metaData);
    connect(reply, &QNetworkReply::finished, [reply, file, this]() {
    if (reply->error() == QNetworkReply::NoError) {
        // The resumable session URI is returned in the Location header
        QUrl sessionUri = reply->header(QNetworkRequest::LocationHeader).toUrl();
        qDebug() << "Resumable upload session started at: " << sessionUri.toString();
        uploadFileInChunks(file, sessionUri);  // Start uploading in chunks
    } else {
        qDebug() << "Error initiating resumable upload: " << reply->errorString();
    }
    reply->deleteLater();
});
}

void GoogleDriveManager::uploadFileInChunks(QFile* file, const QUrl& sessionUrl) {

}

void GoogleDriveManager::authenticate() {
    oauth.grant();
}
