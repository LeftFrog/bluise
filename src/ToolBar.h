#pragma once
#include <QToolBar>
#include "BeautifulButton.h"
#include "BeautifulButtonGroup.h"

class ToolBar : public QWidget {
  Q_OBJECT
public:
  ToolBar(QWidget *parent = nullptr);
protected:
  virtual void resizeEvent(QResizeEvent *event) override;
private:
  BeautifulUi::BeautifulButtonGroup *group;
};