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
    static GoogleDriveManager* getInstance(QObject* parent = nullptr);
    static void destroyInstance();
    ~GoogleDriveManager() override;
    void initOAuth();
    void loadToken();
    QString getFileName(const QString& fileId);
    bool isReady() const;

public slots:
    void authenticate();
    void refreshAccessToken();
    void startUpload(const QString& localFilePath);
    void uploadFile(const QString& localFilePath);
    QNetworkRequest prepareChunkRequest(const QUrl& sessionUrl, qint64 fileSize, qint64 bytesSent, qint64 currentChunkSize) const;
    void uploadFileInChunks(QFile* file, const QUrl& sessionUrl);
    void downloadFile(const QString& fileId);
    void listFiles();

signals:
    void uploadFinished();
    void fileListReceived(QStringList);

private:
    explicit GoogleDriveManager(QObject* parent = nullptr);
    void saveTokens() const;
    QString createFolder(const QString& folderName, const QString& parentId = "");

    static GoogleDriveManager* instance;
    QString bluiseFolderId;
    QString clientId;
    QString clientSecret;
    QOAuth2AuthorizationCodeFlow oauth;
    QNetworkAccessManager networkManager;
};