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
    QString path = QFileDialog::getOpenFileName();
    pic = QPixmap(path);
}

void ChoosePictureWidget::setPicture(const QString & path)
{
    pic = QPixmap(path);
}

QSize ChoosePictureWidget::sizeHint() const
{
return QSize(430, 215);
}

ChoosePictureWidget::ChoosePictureWidget(QWidget* parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    resize(430, 215);
}