#pragma once
#include <QWidget>

class ChoosePictureWidget : public QWidget
{
Q_OBJECT

private:
    QPixmap pic;
public slots:
    void setPicture(const QString& path);
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
public:
    virtual QSize sizeHint() const override;
    ChoosePictureWidget(QWidget* parent = nullptr);
};