//
// Created by Leonov Oleksandr on 9/16/24.
//

#pragma once
#include <QTabWidget>

class SettingsWidget : public QTabWidget {
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget* parent = nullptr);

private:
    void saveSettings();
    void loadSettings();
};
