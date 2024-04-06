#pragma once
#include <QMainWindow>
#include <QListView>
#include "GameListModel.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
private slots:
  void addGame(QAction* action);
private:
  GameListModel model;
  // GameInfoWidget *info;
  QListView *list;
  QMenuBar *menuBar;
};
