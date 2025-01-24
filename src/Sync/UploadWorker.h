//
// Created by Leonov Oleksandr on 11/24/24.
//

#pragma once
#include <QFile>
#include <QNetworkAccessManager>
#include <QUrl>

class UploadWorker : public QObject {
    Q_OBJECT

public:
    explicit UploadWorker(const QString localFilePath, const QString folderId, const QString& accessToken);
    void startUpload();

signals:
    void finished();
    void error(const QString& error);

private slots:
    void initiateResumableSession();
    void uploadNextChunk();

private:
    QString localFilePath;
    QString folderId;
    QString accessToken;
    QFile* file;
    QUrl sessionUrl;
    QNetworkAccessManager networkManager;
    qint64 bytesSent = 0;
    const qint64 chunkSize = 256 * 1024;  // 256 KB

    void handleSessionReply(QNetworkReply* reply);
    void handleChunkReply(QNetworkReply* reply);
};