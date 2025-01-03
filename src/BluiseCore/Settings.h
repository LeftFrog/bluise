//
// Created by Leonov Oleksandr on 10/2/24.
//

#pragma once
#include <QSettings>

class Settings : public QSettings {
public:
    static Settings* getInstance(QObject* parent = nullptr);

    void setAccessToken(const QString& token);
    QString accessToken() const;

    void setRefreshToken(const QString& token);
    QString refreshToken() const;

    void setBluiseFolderId(const QString& folderId);
    QString bluiseFolderId() const;

private:
    static Settings* instance;
    explicit Settings(QObject* parent = nullptr);
};

