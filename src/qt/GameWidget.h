#pragma once
#include <QtWidgets>
#include "QGame.h"

class GameWidget : public QWidget {
    Q_OBJECT
public:
    GameWidget(QGame* _game, QWidget *parent = nullptr);
    virtual QSize sizeHint() const override;
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
private:
    QGame* game;
    char color_mod = 0;
    QRect control_panel;
    QPushButton* play_butt;
    QPushButton* sett_butt;
public slots:
    void play();
};