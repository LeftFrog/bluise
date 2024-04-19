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
  button->move(buttons.indexOf(button)*button->sizeHint().width(), 0);
  resize(button->sizeHint().width()*buttons.size(), height());
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