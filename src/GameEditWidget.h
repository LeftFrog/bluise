#pragma once
#include "GameOptionsWidget.h"

class GameEditWidget : public GameOptionsWidget {
    Q_OBJECT

public:
    GameEditWidget(Game* _game, QWidget* parent = nullptr);
private:
    Game* game;
protected slots:
    virtual void apply() override;
    void changed();
signals:
    void gameChanged();
};