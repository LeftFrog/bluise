#pragma once 
#include <QWidget>
#include "BeautifulButton.h"
#include <QButtonGroup>
#include <QHBoxLayout>

namespace BeautifulUi {

class BeautifulButtonGroup : public QWidget {
  Q_OBJECT
public:
  explicit BeautifulButtonGroup(QWidget *parent = nullptr);
  ~BeautifulButtonGroup();
  void addButton(BeautifulButton *button);
  void setExclusive(bool exclusive);

protected:
  void paintEvent(QPaintEvent *event) override;
  void enterEvent(QEnterEvent *event) override;
  void leaveEvent(QEvent *event) override;
  
private:
  bool hovered = false;
  QButtonGroup *buttonGroup;
  QList<BeautifulButton*> buttons;
  QHBoxLayout *layout;
};

}