#include "GameWidget.h"

GameWidget::GameWidget( QWidget *parent) : QWidget(parent) {
    //setSizePolicy(QSizePolicy::Fixed);
    setMinimumSize(QSize(260, 145));
    setMouseTracking(true);
}

QSize GameWidget::sizeHint() const {
    return QSize(260, 145);
}

void GameWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    QColor widcol = palette().color(QPalette::Window);
    widcol.setRgb(widcol.red()+color_mod, widcol.green()+color_mod, widcol.blue()+color_mod, widcol.alpha());
    painter.setBrush(QBrush(widcol, Qt::SolidPattern));
    painter.drawRoundedRect(rect(), 10, 10);
    painter.setBrush(QBrush(QPixmap("/home/leftfrog/Downloads/header.jpg").scaled(width()-10, height()-30)));
    painter.drawRect(10, 10, width() - 20, height()-50);
    painter.setPen(QPen(palette().color(QPalette::WindowText), 3));
    painter.setFont(QFont("Arial", 11));
    painter.drawText(QRect(15, height()-20, 100, 20), Qt::AlignLeft, "Baldur's Gate");
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(palette().color(QPalette::Active, QPalette::ColorRole::Button), Qt::SolidPattern));
    painter.drawRoundedRect(play_button, 5, 5);
    QImage play_button_img = QImage("/home/leftfrog/Downloads/play.png");
    play_button = QRect(width()-40, height()-35, 30, 30);
    painter.drawImage(play_button, play_button_img.scaled(30, 30));
    QWidget::paintEvent(event);
}

void GameWidget::mouseMoveEvent(QMouseEvent *event) {
    if(!rect().contains(event->pos())) {
        color_mod = 0;
        repaint();
    }
    else {
        color_mod = 10;
        repaint();
    }
    QWidget::mouseMoveEvent(event);
}