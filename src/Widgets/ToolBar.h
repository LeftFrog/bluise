#pragma once
#include <QToolBar>
#include "../BeautifulUI/BeautifulButton.h"
#include "../BeautifulUI/BeautifulButtonGroup.h"
#include "SearchBar.h"

class ToolBar : public QWidget {
  Q_OBJECT
public:
  ToolBar(QWidget *parent = nullptr);
signals:
  void setSort(int role);
  void addGame();
  void setFilter(const QString& filer);
  void setName(const QString& name);
protected:
  virtual void resizeEvent(QResizeEvent *event) override;
private:
  SearchBar *search;
  // BeautifulUi::BeautifulButtonGroup *group;
  BeautifulUi::BeautifulButton *optionsButton;
  BeautifulUi::BeautifulButton *addButton;
  BeautifulUi::BeautifulButton *sortButton;
private slots:
  void filter(QAction* action);
  void sort(QAction* action);
};