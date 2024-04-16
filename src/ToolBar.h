#pragma once
#include <QToolBar>

class ToolBar : public QToolBar {
  Q_OBJECT
public:
  ToolBar(QWidget *parent = nullptr);
};