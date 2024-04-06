#pragma once
#include <QMainWindow>
#include <QListView>
#include "GameListModel.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
private:
  GameListModel model;
  // GameInfoWidget *info;
  QListView *list;
};
