//
// Created by Leonov Oleksandr on 8/27/24.
//

#pragma once
#include "AbstractBeautifulButton.h"

class MenuButton : public BeautifulUi::AbstractBeautifulButton {
    Q_OBJECT

public:
    explicit MenuButton(QWidget* parent = nullptr);
    explicit MenuButton(QMenu* menu, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QMenu* menu;
};
