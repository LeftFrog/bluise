#pragma once
#include <QMainWindow>
#include <QListView>
#include <QTableView>

class MainWindow : public QMainWindow {
  Q_OBJECT
  
public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

private slots:
  void handleMenus(QAction* action);
  void addGame();

private:
  QTableView *table;
  QListView *list;
  QMenuBar *menuBar;
  QToolBar *toolBar;
};
