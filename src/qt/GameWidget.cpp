#include "GameWidget.h"

GameWidget::GameWidget( QWidget *parent) : QWidget(parent) {
    setMinimumSize(sizeHint());
    resize(sizeHint());
    setMouseTracking(true);
    control_panel = QRect(0, height()-height()/4, width(), height()/4);
    play_butt = new QPushButton(this);
    play_butt->setGeometry(QRect(control_panel.width()*3/5, control_panel.y() + 5, control_panel.width()/5, control_panel.height()-10));
    play_butt->setText("Play");
    sett_butt = new QPushButton(this);
    sett_butt->setGeometry(QRect(control_panel.width()*4/5, control_panel.y() + 5, control_panel.width()/5, control_panel.height()-10));
    sett_butt->setText("Settings");
    play_butt->setToolTip("Play");
    QLabel *name = new QLabel("Baldur's gate" ,this);
    name->setGeometry(control_panel.x()+5, control_panel.y(), control_panel.width()*3/5, control_panel.height());
}

QSize GameWidget::sizeHint() const {
    return QSize(260, 145);
}

void GameWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    color_mod = 5;
    QColor widcol = palette().color(QPalette::Window);
    widcol.setRgb(widcol.red()+color_mod, widcol.green()+color_mod, widcol.blue()+color_mod, widcol.alpha());
    painter.setBrush(QBrush(QPixmap("/home/leftfrog/Documents/Bluise/icons/Baldur's gate_header.jpg").scaled(QSize(width(), height()*3/4))));
    painter.drawRoundedRect(rect(), 10, 10);
    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, QColor(widcol.red(), widcol.green(), widcol.blue(), 0));
    gradient.setColorAt(0.5, QColor(widcol.red(), widcol.green(), widcol.blue(), 0));
    gradient.setColorAt(0.75, QColor(widcol.red(), widcol.green(), widcol.blue(), 255));
    gradient.setColorAt(1, QColor(widcol.red(), widcol.green(), widcol.blue(), 255));
    painter.setBrush(gradient);
    painter.drawRoundedRect(rect(), 10, 10);
    QWidget::paintEvent(event);
}

void GameWidget::mouseMoveEvent(QMouseEvent *event) {
    // if(!rect().contains(event->pos())) {
    //     color_mod = 0;
    //     repaint();
    // }
    // else {
    //     color_mod = 10;
    //     repaint();
    // }
    QWidget::mouseMoveEvent(event);
}