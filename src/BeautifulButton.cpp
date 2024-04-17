#include "BeautifulButton.h"
#include <QPainter>

BeautifulUi::BeautifulButton::BeautifulButton(QWidget *parent) : QAbstractButton(parent) {
  setCheckable(true);
}

BeautifulUi::BeautifulButton::~BeautifulButton() {
  delete menu;
}

void BeautifulUi::BeautifulButton::setMenu(QMenu *menu) {
  this->menu = menu;
  resize(sizeHint().width()+10, sizeHint().height());
}

void BeautifulUi::BeautifulButton::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(Qt::NoPen);
  if(isChecked()) {
    painter.setBrush(QColor(0, 0, 0, 15));
  } else {
    painter.setBrush(QColor(0, 0, 0, 0));
  }
  painter.drawRoundedRect(rect(), 5, 5);
  if (menu) {
    QRect mainButtonRect = rect();
    mainButtonRect.setWidth(rect().width()-20);
    icon().paint(&painter, mainButtonRect, Qt::AlignCenter, isChecked() ? QIcon::Selected : QIcon::Normal);
    QRect menuButtonRect = rect();
    menuButtonRect.setX(rect().width()-20);
    mainButtonRect.setWidth(20);
    paintMenuButton(painter, menuButtonRect);
  }
  else {
      icon().paint(&painter, rect(), Qt::AlignCenter, isChecked() ? QIcon::Selected : QIcon::Normal);
  }
}

void BeautifulUi::BeautifulButton::paintMenuButton(QPainter &painter, const QRect &rect) {
  QPen pen;
  pen.setColor(palette().color(QPalette::Text));
  painter.setPen(pen);
  painter.drawLine(rect.topLeft().x()+5, rect.topLeft().y()+height()/2-2, rect.center().x(), rect.topLeft().y()+height()/2+2);
  painter.drawLine(rect.center().x(), rect.topLeft().y()+height()/2+2, rect.topRight().x()-6, rect.topLeft().y()+height()/2-2);
  painter.setPen(Qt::NoPen);
}

QSize BeautifulUi::BeautifulButton::sizeHint() const {
  return QSize(40, 25);
}