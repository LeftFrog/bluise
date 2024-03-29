#pragma once 
#include <QQuickWidget>
#include <QQuickItem>

class Dock : public QQuickWidget {
  Q_OBJECT
public:
  Dock(QWidget *parent = nullptr);
public slots: 
  void addGame();
};