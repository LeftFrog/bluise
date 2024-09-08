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
    const qint64 chunkSize = 262144; // 256 KB
    qint64 fileSize = file->size();
    qint64 bytesSent = 0;

    while (bytesSent < fileSize) {
        qint64 remainingBytes = fileSize - bytesSent;
        qint64 currentChunkSize = qMin(chunkSize, remainingBytes);
        QByteArray chunkData = file->read(currentChunkSize);

        QNetworkRequest chunkRequest(sessionUrl);

        QString token = oauth.token();
        if (token.isEmpty()) {
            qDebug() << "Access token is empty.";
            return;
        }
        chunkRequest.setRawHeader("Authorization", "Bearer " + token.toUtf8());

        QString contentRange = QString("bytes %1-%2/%3")
                                            .arg(bytesSent)
                                            .arg(bytesSent + currentChunkSize - 1)
                                            .arg(fileSize);
        chunkRequest.setRawHeader("Content-Range", contentRange.toUtf8());

        QNetworkReply* chunkReply = networkManager.put(chunkRequest, chunkData);
        connect(chunkReply, &QNetworkReply::finished, [chunkReply, &bytesSent, currentChunkSize, file]() {
            if (chunkReply->error() == QNetworkReply::NoError) {
                qDebug() << "Chunk uploaded successfully.";
                bytesSent += currentChunkSize;
            } else {
                qDebug() << "Error uploading chunk: " << chunkReply->errorString();
            }
            chunkReply->deleteLater();
        });

        if (remainingBytes == currentChunkSize) {
            break;  // Upload complete
        }
    }

    qDebug() << "File uploaded successfully!";
}

void GoogleDriveManager::authenticate() {
    oauth.grant();
}
