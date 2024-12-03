//
// Created by Leonov Oleksandr on 9/16/24.
//

#include "SettingsWidget.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

SettingsWidget::SettingsWidget(QWidget* parent) : QTabWidget(parent) {
    // loadSettings();

    QWidget* sync = new QWidget(this);
    QWidget* general = new QWidget(this);
    QWidget* appearance = new QWidget(this);

    //addTab(general, "General");
    addTab(sync, "Sync");
    //addTab(appearance, "Appearance");

    auto* VBL = new QVBoxLayout();
    auto* HBL = new QHBoxLayout();
    QLabel* googledriveAccount = new QLabel("Google Drive account: ");
    signin = new QPushButton();
    connect(&GoogleDriveManager::instance(), &GoogleDriveManager::authorized, this, &SettingsWidget::updateGoogleDriveAccount);
    connect(&GoogleDriveManager::instance(), &GoogleDriveManager::singedOut, this, &SettingsWidget::updateGoogleDriveAccount);
    updateGoogleDriveAccount();

    HBL->addWidget(googledriveAccount);
    HBL->addWidget(signin);
    VBL->addLayout(HBL);
    sync->setLayout(VBL);
}

void SettingsWidget::updateGoogleDriveAccount() {
    if (!GoogleDriveManager::instance().isReady()) {
        signin->setText("Sing in");
        connect(signin, &QPushButton::clicked, &GoogleDriveManager::instance(), &GoogleDriveManager::authenticate);
    }
    else {
        signin->setText("Sign out");
        connect(signin, &QPushButton::clicked, &GoogleDriveManager::instance(), &GoogleDriveManager::singOut);
    }
}
