#include "ToolBar.h"
#include <QPushButton>

ToolBar::ToolBar(QWidget *parent) : QToolBar(parent) {
  setMovable(false);
  setFloatable(false);
}