//
// Created by Leonov Oleksandr on 8/23/24.
//

#pragma once
#include "QtAwesome.h"

class IconHandler final : public QObject {
    Q_OBJECT

public:
    explicit IconHandler(QObject* parent = nullptr);
    QIcon getIcon(int style, int icon);
    void initFontAwesome();

private:
    fa::QtAwesome* awesome;
};