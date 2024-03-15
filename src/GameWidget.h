#pragma once
//#include <QtWidgets>
#include <QQuickWidget>
#include <QQuickItem>
// #include <QWidget>
// #include <QPushButton>
// #include <QObject>
#include "Game.h"

class GameWidget : public QQuickWidget {
    Q_OBJECT
public:
    GameWidget(Game* _game, QWidget *parent = nullptr);
    virtual QSize sizeHint() const override;
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
private:
    Game* game;
public slots:
    void play();
};