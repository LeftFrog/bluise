//
// Created by Leonov Oleksandr on 10/2/24.
//

#pragma once
#include <QSettings>

class Settings : public QSettings {
public:
    static Settings* getInstance();

    void setAccessToken(const QString& token);
    QString accessToken() const;

private:
    static Settings* instance;
    explicit Settings(QObject* parent = nullptr);
};

