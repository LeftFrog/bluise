#include "BeautifulButton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QStyleHints>

BeautifulUi::BeautifulButton::BeautifulButton(QWidget *parent) : QAbstractButton(parent) {
  setCheckable(true);
  setMouseTracking(true);
  setAttribute(Qt::WA_Hover, true);
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
  QColor color = QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark ? Qt::white : Qt::black;

  color.setAlpha(hovered ? 10 : 0);
  color.setAlpha(isChecked() ? 15 : color.alpha());
  painter.setBrush(color);

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
    QRect buttonRect = rect();
    icon().paint(&painter, buttonRect, Qt::AlignCenter, isChecked() ? QIcon::Selected : QIcon::Normal);
  }
}

void BeautifulUi::BeautifulButton::paintMenuButton(QPainter &painter, const QRect &rect) {
  QPen pen;
  pen.setColor(palette().color(QPalette::Text));
  pen.setWidth(1);
  painter.setPen(pen);
  painter.drawLine(rect.topLeft().x()+5, rect.center().y()-2, rect.center().x(), rect.center().y()+2);
  painter.drawLine(rect.center().x(), rect.center().y()+2, rect.topRight().x()-6, rect.center().y()-2);
  painter.setPen(Qt::NoPen);
}

void BeautifulUi::BeautifulButton::enterEvent(QEnterEvent *event) {
  if(group()) {
    return;
  }
  hovered = true;
  update();
  QAbstractButton::enterEvent(event);
}

void BeautifulUi::BeautifulButton::leaveEvent(QEvent *event) {
  if(group()) {
    return;
  }
  hovered = false;
  update();
  QAbstractButton::leaveEvent(event);
}

void BeautifulUi::BeautifulButton::mouseReleaseEvent(QMouseEvent *event) {
  if (menu && rect().contains(event->pos())) {
    setChecked(true);
    menu->exec(mapToGlobal(rect().bottomLeft()));
  }
  QAbstractButton::mouseReleaseEvent(event);
}

QSize BeautifulUi::BeautifulButton::sizeHint() const {
  return QSize(40, 30);
}