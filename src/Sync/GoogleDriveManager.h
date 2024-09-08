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

private:
    QOAuth2AuthorizationCodeFlow oauth;
    QNetworkAccessManager networkManager;
};