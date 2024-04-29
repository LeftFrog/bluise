#include "BeautifulButton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QStyleHints>
#include <QApplication>

BeautifulUi::BeautifulButton::BeautifulButton(QWidget *parent) : QAbstractButton(parent) {
  setCheckable(true);
  setMouseTracking(true);
  setAttribute(Qt::WA_Hover, true);
  awesome = new fa::QtAwesome(this);
  awesome->initFontAwesome();
}

BeautifulUi::BeautifulButton::~BeautifulButton() {
  delete menu;
}

void BeautifulUi::BeautifulButton::setMenu(QMenu *menu) {
  this->menu = menu;
  resize(sizeHint().width()+20, sizeHint().height());
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

  painter.drawRoundedRect(rect(), 6, 6);
  if (menu) {
    QRect mainButtonRect = rect();
    mainButtonRect.setWidth(rect().width()-18);
    mainButtonRect.setX(6);
    icon().paint(&painter, mainButtonRect, Qt::AlignCenter, isChecked() ? QIcon::Selected : QIcon::Normal);
    QRect menuButtonRect = rect();
    menuButtonRect.setX(mainButtonRect.width()+10);
    menuButtonRect.setWidth(12);
    paintMenuButton(painter, menuButtonRect);
  }
  else {
    QRect buttonRect = QRect(rect().x() + 4, rect().y() + 3, rect().width() - 8 , rect().height()-6);
    icon().paint(&painter, buttonRect, Qt::AlignCenter, isChecked() ? QIcon::Selected : QIcon::Normal);
  }
}

void BeautifulUi::BeautifulButton::paintMenuButton(QPainter &painter, const QRect &rect) {
  QIcon icon = awesome->icon(fa::fa_solid, fa::fa_chevron_down);
  icon.paint(&painter, rect, Qt::AlignCenter, QIcon::Normal);
}

void BeautifulUi::BeautifulButton::enterEvent(QEnterEvent *event) {
  if(group()) {
    QApplication::sendEvent(parent(), event);
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
  return QSize(45, 30);
}