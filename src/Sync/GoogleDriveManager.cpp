//
// Created by Leonov Oleksandr on 9/8/24.
//

#include "GoogleDriveManager.h"
#include <QApplication>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <qcoreapplication.h>
#include <QDesktopServices>
#include <QDir>
#include <QFileInfo>
#include <QHttpMultiPart>
#include <QMimeDatabase>
#include <QNetworkReply>
#include <QOAuthHttpServerReplyHandler>
#include <QThread>
#include "../BluiseCore/Settings.h"
#include <QtConcurrent>
#include <QEventLoop>

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
    loadTokens();

    connect(this, &GoogleDriveManager::authorized, &GoogleDriveManager::initializeBluiseFolderId);
}

GoogleDriveManager::~GoogleDriveManager() {
    saveTokens();
    saveBluiseFolderId(bluiseFolderId);
    qDeleteAll(uploadWorkers);
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

void GoogleDriveManager::loadTokens() {
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
        qDebug() << "Bluise folder ID is empty. Trying to find it.";
        bluiseFolderId = findFolder("Bluise");
        if(bluiseFolderId.isEmpty()) {
            qDebug() << "Bluise folder not found. Creating it.";
            bluiseFolderId = createFolder("Bluise");
        }
        saveBluiseFolderId(bluiseFolderId);
    }
}

QString GoogleDriveManager::findFolder(const QString& folderName) {
    QString folderId= "";

    QNetworkRequest request(QUrl("https://www.googleapis.com/drive/v3/files?q=name='" + folderName + "' and mimeType='application/vnd.google-apps.folder'"));
    request.setRawHeader("Authorization", "Bearer " + oauth.token().toUtf8());

    QNetworkReply* reply = networkManager.get(request);
    QEventLoop eventLoop;

    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray filesArray = jsonObject["files"].toArray();

        if(!filesArray.isEmpty()) {
            folderId = filesArray[0].toObject()["id"].toString();
            qDebug() << "Folder ID " << folderId;
        } else {
            qDebug() << "Folder not found.";
        }
    } else {
        qDebug() << "Error finding error: " << reply->errorString();
    }
    reply->deleteLater();

    return folderId;
}

void GoogleDriveManager::loadBluiseFolderId() {
    bluiseFolderId = Settings::getInstance()->bluiseFolderId();
}

void GoogleDriveManager::saveBluiseFolderId(const QString& folderId) {
    Settings::getInstance()->setBluiseFolderId(folderId);
}

/* File Management */
void GoogleDriveManager::uploadFile(const QString& localFilePath, const QString& folderId) {
    if (!isReady()) {
        qDebug() << "Not authenticated!";
        return;
    }

    QString targetFolderId = folderId.isEmpty() ? bluiseFolderId : folderId;
    UploadWorker* worker = new UploadWorker(localFilePath, targetFolderId, oauth.token());

    QThread* thread = new QThread;
    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &UploadWorker::startUpload);
    connect(worker, &UploadWorker::finished, this, [this, worker, thread]() {
        emit uploadFinished();
        uploadWorkers.removeAll(worker);
        worker->deleteLater();
        thread->quit();
    });
    connect(worker, &UploadWorker::error, this, [](const QString& error) {
        qDebug() << "Upload error:" << error;
    });
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    uploadWorkers.append(worker);
    thread->start();
}

void GoogleDriveManager::uploadFolder(const QString& folderPath, const QString& parentId) {
    // Ensure folderPath is valid
    QDir folderDir(folderPath);
    if (!folderDir.exists()) {
        qWarning() << "Folder path does not exist:" << folderPath;
        return;
    }

    // Start uploading in a worker thread
    QThread* thread = new QThread;
    QObject* worker = new QObject; // Worker context
    worker->moveToThread(thread);

    connect(thread, &QThread::started, this, [this, folderDir, parentId, worker]() {
        try {
            // Iterate through files in the folder
            foreach (QString fileName, folderDir.entryList(QDir::Files)) {
                QString filePath = folderDir.absoluteFilePath(fileName);
                uploadFile(filePath, parentId); // Signal to upload file
            }
            foreach (QString subFolderName, folderDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
                QString subFolderPath = folderDir.absoluteFilePath(subFolderName);
                uploadFolder(subFolderPath, parentId); // Recursive call
            }

            // Clean up
            emit uploadFinished(); // Signal upload completion
        } catch (const std::exception& e) {
        }
    });

    connect(this, &GoogleDriveManager::uploadFinished, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(thread, &QThread::finished, worker, &QObject::deleteLater);

    thread->start();
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