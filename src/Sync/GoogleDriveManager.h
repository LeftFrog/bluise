//
// Created by Leonov Oleksandr on 9/8/24.
//

#pragma once
#include <QNetworkAccessManager>
#include <QOAuth2AuthorizationCodeFlow>

class GoogleDriveManager : public QObject {
    Q_OBJECT

public:
    explicit GoogleDriveManager(QObject* parent = nullptr);

public slots:
    void authenticate();
    void uploadFile(const QString& localFilePath, const QString& remoteFilePath);

private:
    QString clientId;
    QString clientSecret;
    QOAuth2AuthorizationCodeFlow oauth;
    QNetworkAccessManager networkManager;
};