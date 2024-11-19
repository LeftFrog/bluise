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
    ~GoogleDriveManager() override;
    void initOAuth();
    void loadToken();

    QString getFileName(const QString& fileId);
    bool isReady() const;

public slots:
    void authenticate();
    void refreshAccessToken();
    void startUpload(const QString& localFilePat, const QString& folderId = "");
    void uploadFile(const QString& localFilePath, const QString& folderId);
    QNetworkRequest prepareChunkRequest(const QUrl& sessionUrl, qint64 fileSize, qint64 bytesSent, qint64 currentChunkSize) const;
    void uploadFileInChunks(QFile* file, const QUrl& sessionUrl);
    void downloadFile(const QString& fileId);
    void listFiles();
    void singOut();
    QString findFolder(const QString& folderName);

signals:
    void uploadFinished();
    void fileListReceived(QStringList);
    void authorized();
    void singedOut();

private slots:
    void initializeBluiseFolderId();

private:
    explicit GoogleDriveManager(QObject* parent = nullptr);
    void saveTokens() const;
    void loadBluiseFolderId();
    void saveBluiseFolderId(const QString& folderId);
    QString createFolder(const QString& folderName, const QString& parentId = "");

    static GoogleDriveManager* instance;
    QString bluiseFolderId;
    QString clientId;
    QString clientSecret;
    QOAuth2AuthorizationCodeFlow oauth;
    QNetworkAccessManager networkManager;
};