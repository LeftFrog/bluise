#pragma once
#include <QWidget>

class ChoosePictureWidget : public QWidget
{
Q_OBJECT

private:
    QPixmap pic;
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
public:
    void setPicture(const QString& path);
    virtual QSize sizeHint() const override;
    ChoosePictureWidget(QWidget* parent = nullptr);
};