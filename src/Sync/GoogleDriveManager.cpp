//
// Created by Leonov Oleksandr on 9/8/24.
//

#include "GoogleDriveManager.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <qcoreapplication.h>
#include <QDesktopServices>
#include <QFileInfo>
#include <QHttpMultiPart>
#include <QMimeDatabase>
#include <QNetworkReply>
#include <QOAuthHttpServerReplyHandler>
#include <QThread>
#include "../BluiseCore/Settings.h"

/* Singleton */
GoogleDriveManager* GoogleDriveManager::instance = nullptr;

GoogleDriveManager* GoogleDriveManager::getInstance(QObject* parent) {
    if (!instance) {
        instance = new GoogleDriveManager(parent);
    }
    return instance;
}

/* Constructor & destructor */
GoogleDriveManager::GoogleDriveManager(QObject* parent) : QObject(parent), oauth(), networkManager() {
    clientId = getenv("GOOGLE_CLIENT_ID");
    clientSecret = getenv("GOOGLE_CLIENT_SECRET");

    if (clientId.isEmpty() || clientSecret.isEmpty()) {
        qDebug() << "Client ID or Client Secret is not set!";
        return;
    }

    initOAuth();

    loadToken();

    connect(this, &GoogleDriveManager::authorized, &GoogleDriveManager::initializeBluiseFolderId);
}

GoogleDriveManager::~GoogleDriveManager() {
    saveTokens();
    saveBluiseFolderId(bluiseFolderId);
}

/* OAuth Initialization and Token Management */
void GoogleDriveManager::initOAuth() {
    oauth.setAuthorizationUrl(QUrl("https://accounts.google.com/o/oauth2/auth"));
    oauth.setAccessTokenUrl(QUrl("https://oauth2.googleapis.com/token"));
    oauth.setClientIdentifier(clientId);
    oauth.setClientIdentifierSharedKey(clientSecret);
    oauth.setScope("https://www.googleapis.com/auth/drive.file");

    auto* replyHandler = new QOAuthHttpServerReplyHandler(8080, this);
    oauth.setReplyHandler(replyHandler);

    connect(&oauth, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);
    connect(&oauth, &QOAuth2AuthorizationCodeFlow::error, this, [](const QString &error) {
        qDebug() << "OAuth error occurred: " << error;
    });
}

void GoogleDriveManager::loadToken() {
    QString refreshToken = Settings::getInstance()->refreshToken();
    if (!refreshToken.isEmpty()) {
        oauth.setRefreshToken(refreshToken);
        refreshAccessToken();
    }
}

void GoogleDriveManager::saveTokens() const {
    Settings::getInstance()->setAccessToken(oauth.token());
    qDebug() << "Access token saved: " << oauth.token();
    Settings::getInstance()->setRefreshToken(oauth.refreshToken());
    qDebug() << "Refresh token saved: " << oauth.refreshToken();
}

void GoogleDriveManager::refreshAccessToken() {
    QNetworkRequest request{QUrl("https://oauth2.googleapis.com/token")};
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QByteArray data;
    data.append("client_id=" + clientId.toUtf8() + "&");
    data.append("client_secret=" + clientSecret.toUtf8() + "&");
    data.append("refresh_token=" + oauth.refreshToken().toUtf8() + "&");
    data.append("grant_type=refresh_token");

    QNetworkReply* reply = networkManager.post(request, data);
    connect(reply, &QNetworkReply::finished, [reply, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
            QJsonObject jsonObject = jsonResponse.object();
            QString accessToken = jsonObject["access_token"].toString();
            QString refreshToken = jsonObject["refresh_token"].toString();

            oauth.setToken(accessToken);
            if (!refreshToken.isEmpty()) {
                oauth.setRefreshToken(refreshToken);
            }

            qDebug() << "Access token refreshed.";
            emit authorized();
        } else {
            qDebug() << "Error refreshing access token: " << reply->errorString();
        }
        reply->deleteLater();
    });
}

bool GoogleDriveManager::isReady() const {
    return !oauth.token().isEmpty();
}

void GoogleDriveManager::authenticate() {
    oauth.grant();
    connect(&oauth, &QOAuth2AuthorizationCodeFlow::granted, this, [this]() {
        qDebug() << "OAuth granted.";
        emit authorized();
    });
}

void GoogleDriveManager::singOut() {
    oauth.setToken("");
    oauth.setRefreshToken("");
    saveTokens();
    emit singedOut();
}

/* Folder Management */
QString GoogleDriveManager::createFolder(const QString& folderName, const QString& parentId) {
    QString folderId = "";

    QNetworkRequest request(QUrl("https://www.googleapis.com/drive/v3/files"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + oauth.token().toUtf8());

    QJsonObject json;
    json["name"] = folderName;
    json["mimeType"] = "application/vnd.google-apps.folder";

    if (!parentId.isEmpty()) {
        json["parents"] = QJsonArray({parentId});
    }

    QByteArray data = QJsonDocument(json).toJson();

    QNetworkReply* reply = networkManager.post(request, data);

    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Folder created successfully.";
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        qDebug() << "Folder ID: " << jsonResponse.object()["id"].toString();
        folderId = jsonResponse.object()["id"].toString();
    } else {
        qDebug() << "Error creating folder: " << reply->errorString();
    }
    reply->deleteLater();

    return folderId;
}

void GoogleDriveManager::initializeBluiseFolderId() {
    loadBluiseFolderId();
    if(bluiseFolderId.isEmpty()) {
        qDebug() << "Bluise folder ID is empty. Creating a new folder.";
        bluiseFolderId = createFolder("Bluise");
        saveBluiseFolderId(bluiseFolderId);
    }
}

void GoogleDriveManager::loadBluiseFolderId() {
    bluiseFolderId = Settings::getInstance()->bluiseFolderId();
}

void GoogleDriveManager::saveBluiseFolderId(const QString& folderId) {
    Settings::getInstance()->setBluiseFolderId(folderId);
}

/* File Management */
void GoogleDriveManager::uploadFile(const QString& localFilePath) {
    QFile* file = new QFile(localFilePath);
    if(!file->open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file";
        return;
    }
    QMimeType mimeType = QMimeDatabase().mimeTypeForFile(localFilePath);

    QNetworkRequest request(QUrl("https://www.googleapis.com/upload/drive/v3/files?uploadType=resumable"));
    request.setRawHeader("Authorization", "Bearer " + oauth.token().toUtf8());
    request.setAttribute(QNetworkRequest::Http2AllowedAttribute, false);
    request.setTransferTimeout(30000);

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

void GoogleDriveManager::startUpload(const QString& localFilePath) {
    QThread* thread = new QThread;

    // Move the GoogleDriveManager to the new thread
    this->moveToThread(thread);

    // Start the thread and initiate the upload in that thread
    connect(thread, &QThread::started, this, [this, localFilePath]() {
        uploadFile(localFilePath);
    });

    // When the upload is finished, clean up the thread
    connect(this, &GoogleDriveManager::uploadFinished, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    // Start the thread
    thread->start();
}

QNetworkRequest GoogleDriveManager::prepareChunkRequest(const QUrl& sessionUrl, qint64 fileSize, qint64 bytesSent, qint64 currentChunkSize) const {
    QNetworkRequest chunkRequest(sessionUrl);

    QString accessToken = oauth.token();
    if (accessToken.isEmpty()) {
        qDebug() << "Access token is empty!";
        return {};
    }
    chunkRequest.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());
    chunkRequest.setTransferTimeout(30000);

    QString contentRange = QString("bytes %1-%2/%3").arg(bytesSent).arg(bytesSent + currentChunkSize - 1).arg(fileSize);
    chunkRequest.setRawHeader("Content-Range", contentRange.toUtf8());

    return chunkRequest;
}

void GoogleDriveManager::uploadFileInChunks(QFile* file, const QUrl& sessionUrl) {
  constexpr qint64 chunkSize = 256 * 1024;  // 256 KB (adjust this size as needed)
    qint64 fileSize = file->size();
    qint64 bytesSent = 0;

    qDebug() << "Starting chunk upload. File size:" << fileSize << "Chunk size:" << chunkSize;

    while (bytesSent < fileSize) {
        qint64 remainingBytes = fileSize - bytesSent;
        qint64 currentChunkSize = qMin(chunkSize, remainingBytes);

        file->seek(bytesSent);
        QByteArray chunkData = file->read(currentChunkSize);
        if (chunkData.size() != currentChunkSize) {
            qDebug() << "Error reading chunk from file.";
            return;
        }

        qDebug() << "Uploading chunk. Bytes sent:" << bytesSent << "Chunk size:" << currentChunkSize;

        // Send the chunk
        QNetworkReply* reply = networkManager.put(prepareChunkRequest(sessionUrl, fileSize, bytesSent, currentChunkSize), chunkData);

        connect(reply, &QNetworkReply::finished, [reply, &bytesSent, currentChunkSize, this]() {
            if (reply->error() == QNetworkReply::NoError) {
                qDebug() << "Chunk uploaded successfully. Bytes sent so far:" << bytesSent + currentChunkSize;
                bytesSent += currentChunkSize;
            } else {
                qDebug() << "Error uploading chunk: " << reply->errorString();
                reply->deleteLater();
                return;  // Exit if there's an error
            }

            reply->deleteLater();
        });
        connect(reply, &QNetworkReply::finished, [reply]() {
            if (reply->error() == QNetworkReply::NoError) {
                qDebug() << "Chunk uploaded successfully.";
            } else {
                qDebug() << "Error uploading chunk: " << reply->errorString();
                qDebug() << "Response code: " << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
                qDebug() << "Response body: " << reply->readAll();
            }
            reply->deleteLater();
        });

        // Wait for the reply to finish before sending the next chunk
        while (!reply->isFinished()) {
            QCoreApplication::processEvents();
        }

        bytesSent += currentChunkSize;

        // Add a small delay to avoid overwhelming the server (optional)
        QThread::msleep(100);
    }

    qDebug() << "File uploaded successfully!";

    emit uploadFinished();
}

QString GoogleDriveManager::getFileName(const QString& fileId) {
    QNetworkRequest request(QUrl("https://www.googleapis.com/drive/v3/files/" + fileId + "?fields=name"));
    request.setRawHeader("Authorization", "Bearer " + oauth.token().toUtf8());

    QNetworkReply* reply = networkManager.get(request);
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();  // Wait for the network reply to finish

    QString fileName;
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonObject = jsonResponse.object();
        fileName = jsonObject["name"].toString();
        qDebug() << "File name: " << fileName;
    } else {
        qDebug() << "Error getting file metadata: " << reply->errorString();
    }
    reply->deleteLater();
    return fileName;
}

void GoogleDriveManager::downloadFile(const QString& fileId) {
    QNetworkRequest request(QUrl("https://www.googleapis.com/drive/v3/files/" + fileId + "?alt=media"));
    request.setRawHeader("Authorization", "Bearer " + oauth.token().toUtf8());

    QNetworkReply* reply = networkManager.get(request);
    connect(reply, &QNetworkReply::finished, [fileId, this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QFile file(getFileName(fileId));
            if (!file.open(QIODevice::WriteOnly)) {
                qDebug() << "Failed to open file for writing.";
                return;
            }
            file.write(reply->readAll());
            file.close();
            qDebug() << "File downloaded successfully.";
        } else {
            qDebug() << "Error downloading file: " << reply->errorString();
        }
        reply->deleteLater();
    });
}

void GoogleDriveManager::listFiles() {
    QNetworkRequest request(QUrl("https://www.googleapis.com/drive/v3/files"));
    request.setRawHeader("Authorization", "Bearer " + oauth.token().toUtf8());

    QNetworkReply* reply = networkManager.get(request);
    connect(reply, &QNetworkReply::finished, [reply, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
            QJsonObject jsonObject = jsonResponse.object();
            QJsonArray filesArray = jsonObject["files"].toArray();

            QStringList fileIds;
            for (const QJsonValue& value : filesArray) {
                QJsonObject fileObject = value.toObject();
                QString fileId = fileObject["id"].toString();
                fileIds.append(fileId);
            }

            emit fileListReceived(fileIds);
        } else {
            qDebug() << "Error listing files: " << reply->errorString();
        }
        reply->deleteLater();
    });
}