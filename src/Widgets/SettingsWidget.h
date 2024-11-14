//
// Created by Leonov Oleksandr on 9/16/24.
//

#pragma once
#include <QTabWidget>
#include <QPushButton>
#include "../Sync/GoogleDriveManager.h"

class SettingsWidget : public QTabWidget {
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget* parent = nullptr);

private slots:
    void updateGoogleDriveAccount();

private:
    QPushButton* signin = new QPushButton();
    void saveSettings();
    void loadSettings();
};
