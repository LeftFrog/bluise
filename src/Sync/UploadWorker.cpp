//
// Created by Leonov Oleksandr on 11/24/24.
//

#include "UploadWorker.h"
#include <QNetworkReply>
#include <QMimeDatabase>
#include <QFileInfo>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

UploadWorker::UploadWorker(const QString localFilePath, const QString folderId, const QString& accessToken)
    : localFilePath(localFilePath), folderId(folderId), accessToken(accessToken), file(localFilePath) { }

void UploadWorker::startUpload() {
    file = new QFile(localFilePath);
    if (!file->open(QIODevice::ReadOnly)) {
        emit error("Failed to open file");
        return;
    }

    initiateResumableSession();
}

void UploadWorker::initiateResumableSession() {
    QNetworkRequest request(QUrl("https://www.googleapis.com/upload/drive/v3/files?uploadType=resumable"));
    request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());
    QMimeType mimeType = QMimeDatabase().mimeTypeForFile(localFilePath);

    QJsonObject metaJson;
    metaJson["name"] = QFileInfo(*file).fileName();
    metaJson["mimeType"] = mimeType.name();
    metaJson["parents"] = QJsonArray({folderId});
    QByteArray metaData = QJsonDocument(metaJson).toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=UTF-8");
    QNetworkReply* reply = networkManager.post(request, metaData);
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        handleSessionReply(reply);
    });
}

void UploadWorker::handleSessionReply(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        emit error("Session error: " + reply->errorString());
        return;
    }

    sessionUrl = reply->header(QNetworkRequest::LocationHeader).toUrl();
    reply->deleteLater();
    uploadNextChunk();
}

void UploadWorker::uploadNextChunk() {
    const qint64 remaining = file->size() - bytesSent;
    if (remaining <= 0) {
        file->close();
        emit finished();
        return;
    }

    const qint64 chunkSize = qMin(chunkSize, remaining);
    file->seek(bytesSent);
    QByteArray chunkData = file->read(chunkSize);

    QNetworkRequest request(sessionUrl);
    request.setRawHeader("Content-Range", QString("bytes %1-%2/%3")
        .arg(bytesSent)
        .arg(bytesSent + chunkSize - 1)
        .arg(file->size()).toUtf8());

    QNetworkReply* reply = networkManager.put(request, chunkData);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() { handleChunkReply(reply); });
}

void UploadWorker::handleChunkReply(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        bytesSent += reply->property("chunkSize").toLongLong();
        uploadNextChunk(); // Proceed to next chunk
    } else {
        emit error("Chunk error: " + reply->errorString());
    }
    reply->deleteLater();
}