#pragma once
#include <QMainWindow>
#include <QListView>
#include <QTableView>
#include "./ModelView/GameListModel.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
private slots:
  void handleMenus(QAction* action);
  void addGame();
private:
  GameListModel model;
  QTableView *table;
  QListView *list;
  QMenuBar *menuBar;
  QToolBar *toolBar;
};
