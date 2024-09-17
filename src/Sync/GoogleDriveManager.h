//
// Created by Leonov Oleksandr on 9/8/24.
//

#pragma once
#include <QNetworkAccessManager>
#include <QOAuth2AuthorizationCodeFlow>
#include <QFile>

class GoogleDriveManager : public QObject {
    Q_OBJECT

public:
    explicit GoogleDriveManager(QObject* parent = nullptr);
    ~GoogleDriveManager() override;
    QString getFileName(const QString& fileId);

public slots:
    void authenticate();
    void refreshAccessToken();
    void startUpload(const QString& localFilePath);
    void uploadFile(const QString& localFilePath);
    void uploadFileInChunks(QFile* file, const QUrl& sessionUrl);
    void downloadFile(const QString& fileId);
    void listFiles();

signals:
    void uploadFinished();
    void fileListReceived(QStringList);

private:

    QString clientId;
    QString clientSecret;
    QOAuth2AuthorizationCodeFlow oauth;
    QNetworkAccessManager networkManager;
};