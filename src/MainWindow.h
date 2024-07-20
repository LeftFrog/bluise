#pragma once
#include <QMainWindow>
#include <QListView>
#include <qsplitter.h>

#include "./Widgets/ToolBar.h"

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

    ToolBar* toolbar;
    QListView* list;
    QMenuBar* menuBar;
};
