#include "ChoosePictureWidget.h"
#include <QPainter>
#include <QFileDialog>



void ChoosePictureWidget::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QPalette pal = QPalette();
    if(!pic.isNull()){
        painter.setBrush(QBrush(pic));
    }
    else {
        painter.setBrush(QBrush(pal.color(QPalette::Midlight)));
    }
    painter.drawRect(rect());
    QWidget::paintEvent(event);

}

void ChoosePictureWidget::mousePressEvent(QMouseEvent * event)
{
    QFileDialog* fd = new QFileDialog(this);
    fd->setNameFilter("*.jpg *.png *.jpeg *.jpe");
    connect(fd, &QFileDialog::fileSelected, this, &ChoosePictureWidget::setPicture);
    fd->exec();
    // QString path = fd->getOpenFileName();
    // pic = QPixmap(path);
}

void ChoosePictureWidget::setPicture(const QString & path)
{
    current_path = path;
    emit changed();
    pic = QPixmap(path).scaled(rect().size());
}

QSize ChoosePictureWidget::sizeHint() const
{
return QSize(430, 215);
}

ChoosePictureWidget::ChoosePictureWidget(const QString& path,QWidget* parent) : QWidget(parent), first_path(path), current_path(path) {
    setAutoFillBackground(true);
    resize(430, 215);
    setFixedSize(430, 215);
    pic = QPixmap(path).scaled(rect().size());
}