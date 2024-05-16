#include "BeautifulButtonGroup.h"
#include <QPainter>
#include <QStyleHints>
#include <QGuiApplication>

BeautifulUi::BeautifulButtonGroup::BeautifulButtonGroup(QWidget *parent) : QWidget(parent) {
  buttonGroup = new QButtonGroup(this);
  buttonGroup->setExclusive(true);
  // resize(0, 0);
}

BeautifulUi::BeautifulButtonGroup::~BeautifulButtonGroup() {
  delete buttonGroup;
}

void BeautifulUi::BeautifulButtonGroup::addButton(BeautifulButton *button) {
  buttons.append(button);
  buttonGroup->addButton(button);
  button->setParent(this);
  button->move(buttons.indexOf(button)*button->sizeHint().width()+1, 0);
  resize(button->sizeHint().width()*buttons.size()+buttons.size()-1, height());
}

void BeautifulUi::BeautifulButtonGroup::setExclusive(bool exclusive) {
  buttonGroup->setExclusive(exclusive);
}

void BeautifulUi::BeautifulButtonGroup::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(Qt::NoPen);
  QColor color = QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark ? Qt::white : Qt::black;
  color.setAlpha(hovered ? 10 : 0);
  painter.setBrush(color);
  painter.drawRoundedRect(rect(), 6, 6);
  if(buttons.size()>=2) {
    color.setAlpha(15);
    QPen pen = QPen(color);
    painter.setPen(pen);
    for(int i = 1; i < buttons.size(); ++i) {
      painter.drawLine(buttons[i]->width()*i+1, 5, buttons[i]->width()*i+1, height()-5);
    }
  }
}

void BeautifulUi::BeautifulButtonGroup::enterEvent(QEnterEvent *event) {
  Q_UNUSED(event);
  hovered = true;
  update();
}

void BeautifulUi::BeautifulButtonGroup::leaveEvent(QEvent *event) {
  Q_UNUSED(event);
  hovered = false;
  update();
}