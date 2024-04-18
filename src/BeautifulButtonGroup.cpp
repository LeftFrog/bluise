#include "BeautifulButtonGroup.h"
#include <QPainter>

BeautifulUi::BeautifulButtonGroup::BeautifulButtonGroup(QWidget *parent) : QWidget(parent) {
  buttonGroup = new QButtonGroup(this);
  buttonGroup->setExclusive(true);
  layout = new QHBoxLayout(this);
  // resize(0, 0);
  setLayout(layout);
}

BeautifulUi::BeautifulButtonGroup::~BeautifulButtonGroup() {
  delete buttonGroup;
}

void BeautifulUi::BeautifulButtonGroup::addButton(BeautifulButton *button) {
  buttons.append(button);
  buttonGroup->addButton(button);
  layout->addWidget(button);
  // button->move(buttons.indexOf(button)*buttons.at(buttons.indexOf(button)-1)->width, 0);
  // resize(width()+button->width(), button->sizeHint().height());
}

void BeautifulUi::BeautifulButtonGroup::setExclusive(bool exclusive) {
  buttonGroup->setExclusive(exclusive);
}

void BeautifulUi::BeautifulButtonGroup::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(Qt::NoPen);
  painter.setBrush(QColor(0, 0, 0, hovered ? 10 : 0));
  painter.drawRoundedRect(rect(), 5, 5);
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