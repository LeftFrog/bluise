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

    addTab(general, "General");
    addTab(sync, "Sync");
    addTab(appearance, "Appearance");

    auto* VBL = new QVBoxLayout();
    auto* HBL = new QHBoxLayout();
    QLabel* googledriveAccount = new QLabel("Google Drive account: ");
    QPushButton* signin = new QPushButton();
    if (GoogleDriveManager::getInstance()->isReady()) {
        signin->setText("Sign out");
    } else {
        signin->setText("Sign in");
        connect(signin, &QPushButton::clicked, GoogleDriveManager::getInstance(), &GoogleDriveManager::authenticate);
    }
    HBL->addWidget(googledriveAccount);
    HBL->addWidget(signin);
    VBL->addLayout(HBL);
    sync->setLayout(VBL);
}
