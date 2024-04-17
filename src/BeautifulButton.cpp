#include "BeautifulButton.h"
#include <QPainter>

BeautifulUi::BeautifulButton::BeautifulButton(QWidget *parent) : QAbstractButton(parent) {
  setCheckable(true);
}

BeautifulUi::BeautifulButton::~BeautifulButton() {
  
}

void BeautifulUi::BeautifulButton::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(Qt::NoPen);
  if(isChecked()) {
    painter.setBrush(QColor(0, 0, 0, 10));
  } else {
    painter.setBrush(QColor(0, 0, 0, 0));
  }
  painter.drawRoundedRect(rect(), 5, 5);
  icon().paint(&painter, rect(), Qt::AlignCenter, isChecked() ? QIcon::Selected : QIcon::Normal);
}