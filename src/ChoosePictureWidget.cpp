#include "ChoosePictureWidget.h"
#include <QFileDialog>
#include <QPainter>

ChoosePictureWidget::ChoosePictureWidget(const QString &path, QWidget *parent)
    : QWidget(parent), firstPath(path), currentPath(path) {
  setAutoFillBackground(true);
  resize(430, 215);
  setFixedSize(430, 215);
  pic = QPixmap(path).scaled(rect().size());
}

void ChoosePictureWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QPalette pal = QPalette();
  if (!pic.isNull()) {
    painter.setBrush(QBrush(pic));
  } else {
    painter.setBrush(QBrush(pal.color(QPalette::Midlight)));
  }
  painter.drawRect(rect());
  QWidget::paintEvent(event);
}

void ChoosePictureWidget::mousePressEvent(QMouseEvent *event) {
  QFileDialog *fd = new QFileDialog(this);
  fd->setNameFilter("*.jpg *.png *.jpeg *.jpe");
  connect(fd, &QFileDialog::fileSelected, this,
          &ChoosePictureWidget::setPicture);
  fd->exec();
}

void ChoosePictureWidget::setPicture(const QString &path) {
  currentPath = path;
  emit changed();
  pic = QPixmap(path).scaled(rect().size());
}

QSize ChoosePictureWidget::sizeHint() const { return QSize(430, 215); }