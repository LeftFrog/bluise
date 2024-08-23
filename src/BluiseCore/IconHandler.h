//
// Created by Leonov Oleksandr on 8/23/24.
//

#pragma once
#include "QtAwesome.h"
#include <QAbstractButton>

class IconHandler final : public QObject {
    Q_OBJECT

public:
    explicit IconHandler(QObject* parent = nullptr);
    QIcon getIcon(int style, int icon);
    void initFontAwesome();

    void registerButton(QAbstractButton* button, int icon);
    void unregisterButton(QAbstractButton* button);

private slots:
    void changeColorScheme(Qt::ColorScheme);

private:
    QHash<QAbstractButton*, int> icons;
    fa::QtAwesome* awesome;
};
