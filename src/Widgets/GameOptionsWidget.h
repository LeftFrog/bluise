#pragma once
#include "ChoosePictureWidget.h"
#include "../BluiseCore/Game.h"
#include "GameOptionWidget.h"
#include <QPushButton>
#include "BoxOptionWidget.h"

class GameOptionsWidget : public QWidget {
    Q_OBJECT

public:
    explicit GameOptionsWidget(QWidget *parent = nullptr);
    explicit GameOptionsWidget(const Game& game, QWidget *parent = nullptr);

protected:
    void init(const Game& game = Game());
    void initOptions(const Game& game);
    QWidget* createGameInfoWidget();
    QWidget* createGameOptionsWidget();

    ChoosePictureWidget *choose;
    QPushButton *applyButton;
    QMap<QString, GameOptionWidget*> options;
    QString setCover();
    BoxOptionWidget* runner;

protected slots:
    virtual void apply() = 0;
    virtual void changed() = 0;
};