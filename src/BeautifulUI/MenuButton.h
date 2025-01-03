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
    explicit MenuButton(const QString& text, QMenu* menu, QWidget* parent = nullptr);

    void setMenu(QMenu* menu);
    void paintDownButtons(QPainter& painter);
    void calcutlateRects();
    void drawDivider(QPainter& painter);
    void drawButtonElements(QPainter& painter);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private slots:
    void hideMenu();

private:
    QRect mainRect;
    QRect menuRect;
    QMenu* menu;
    bool isMenuDown = false;
};
