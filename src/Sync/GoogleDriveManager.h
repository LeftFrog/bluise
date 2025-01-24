//
// Created by Leonov Oleksandr on 9/8/24.
//

#pragma once
#include <QNetworkAccessManager>
#include <QOAuth2AuthorizationCodeFlow>
#include <QMutex>
#include <QThread>
#include "UploadWorker.h"

class GoogleDriveManager : public QObject {
    Q_OBJECT

public:
    static GoogleDriveManager* getInstance(QObject* parent = nullptr);
    ~GoogleDriveManager() override;

    QString getFileName(const QString& fileId);
    bool isReady() const;

public slots:
    void authenticate();
    void refreshAccessToken();
    void uploadFile(const QString& localFilePath, const QString& folderId = "");
    void uploadFolder(const QString& folderPath, const QString& parentId = "");
    void downloadFile(const QString& fileId);
    void listFiles();
    void singOut();

signals:
    void uploadFinished();
    void fileListReceived(QStringList);
    void authorized();
    void singedOut();

private slots:
    void initializeBluiseFolderId();

private:
    explicit GoogleDriveManager(QObject* parent = nullptr);

    void initOAuth();
    void loadTokens();
    void saveTokens() const;
    void loadBluiseFolderId();
    void saveBluiseFolderId(const QString& folderId);
    QString createFolder(const QString& folderName, const QString& parentId = "");
    QString findFolder(const QString& folderName);

    static GoogleDriveManager* instance;
    QString bluiseFolderId;
    QString clientId;
    QString clientSecret;
    QOAuth2AuthorizationCodeFlow oauth;
    QNetworkAccessManager networkManager;
    QList<UploadWorker*> uploadWorkers;
};
