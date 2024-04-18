#pragma once 
#include <QWidget>
#include "BeautifulButton.h"
#include <QButtonGroup>

namespace BeautifulUi {

class BeautifulButtonGroup : public QWidget {
  Q_OBJECT
public:
  explicit BeautifulButtonGroup(QWidget *parent = nullptr);
  ~BeautifulButtonGroup();
  void addButton(BeautifulButton *button);
  void setExclusive(bool exclusive);

private:
  QButtonGroup *buttonGroup;
  QList<BeautifulButton*> buttons;
};

}