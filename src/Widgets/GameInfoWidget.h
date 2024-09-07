#pragma once
#include <QLabel>
#include "../BluiseCore/Game.h"
#include <QMenu>
#include <QVBoxLayout>
#include "../BeautifulUI/MenuButton.h"
#include "../QtAwesome/QtAwesome/QtAwesome.h"

class GameInfoWidget : public QWidget {
    Q_OBJECT

public:
    explicit GameInfoWidget(QWidget* parent = nullptr);

signals:
    void removeSignal();

public slots:
    void setGame(const QModelIndex& index);

private slots:
    void play();
    void settings();
    void popupMenu();
    void removeGame();
    void openWorkingDirectory();

private:
    QMenu* createMenu();
    MenuButton* createMenuButton();
    QLabel* createLabel();
    QHBoxLayout* createLayout();

    QLabel* label;
    const Game* game;
    QMenu* menu;
};
