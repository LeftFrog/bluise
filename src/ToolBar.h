#pragma once
#include <QToolBar>
#include "BeautifulButton.h"
#include "BeautifulButtonGroup.h"
#include <QLineEdit>

class ToolBar : public QWidget {
  Q_OBJECT
public:
  ToolBar(QWidget *parent = nullptr);
signals:
  void addGame();
protected:
  virtual void resizeEvent(QResizeEvent *event) override;
private:
  QLineEdit *search;
  BeautifulUi::BeautifulButtonGroup *group;
  BeautifulUi::BeautifulButton *optionsButton;
  BeautifulUi::BeautifulButton *addButton;
};