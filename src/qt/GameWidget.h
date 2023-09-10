#pragma once
#include <QtWidgets>
#include "QGame.h"

class GameWidget : public QWidget {
public:
    GameWidget(QWidget *parent = nullptr);
    virtual QSize sizeHint() const override;
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
private:
    char color_mod = 0;
    QRect play_button;
    QPushButton* play_butt;
    QPushButton* sett_butt;
};