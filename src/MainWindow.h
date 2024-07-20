#pragma once
#include <QMainWindow>
#include <QListView>
#include <QSplitter>

#include "./Widgets/ToolBar.h"
#include "Widgets/GameInfoWidget.h"

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void handleMenus(QAction* action);
    void addGame();

private:
    void initMenuBar();
    void initListView();
    void initToolBar();
    GameInfoWidget* createGameInfoWidget();
    QSplitter* createSplitter();

    ToolBar* toolbar;
    QListView* list;
    QMenuBar* menuBar;
};
