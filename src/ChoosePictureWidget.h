#pragma once
#include <QWidget>

class ChoosePictureWidget : public QWidget
{
Q_OBJECT

private:
    QPixmap pic;
    QString first_path;
    QString current_path;
public slots:
    void setPicture(const QString& path);
signals:   
    void changed();
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
public:
    virtual QSize sizeHint() const override;
    QString path() const { return current_path; }
    ChoosePictureWidget(const QString& path = "", QWidget* parent = nullptr);
    bool isChanged() const { return current_path != first_path; qDebug() << first_path << " " << current_path; }
};