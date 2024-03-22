#pragma once
#include <QWidget>
#include <QPushButton>
#include "Game.h"
#include "GameOptionWidget.h"

class GameEditWidget : public QWidget {
    Q_OBJECT

public:
    GameEditWidget(Game* _game, QWidget* parent = nullptr);
private:
    Game* game;
    QPushButton* applyButton;
    GameOptionWidget* name;
    GameOptionWidget* working_directory;
    GameOptionWidget* exec;
    GameOptionWidget* save_path;
private slots:
    void closeWin();
    void apply();
    void changed();
signals:
    void gameChanged();
};