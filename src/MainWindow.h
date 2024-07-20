#pragma once
#include <QMainWindow>
#include <QListView>

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

    QListView* list;
    QMenuBar* menuBar;
};
