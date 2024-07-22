#pragma once
#include <QWidget>

class ChoosePictureWidget : public QWidget {
    Q_OBJECT

public:
    virtual QSize sizeHint() const override;
    QString path() const { return currentPath; }
    ChoosePictureWidget(const QString& path = "", QWidget* parent = nullptr);

    bool isChanged() const {
        return currentPath != firstPath;
    }

public slots:
    void setPicture(const QString& path);
signals:
    void changed();

protected:
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;

private:
    QPixmap pic;
    QString firstPath;
    QString currentPath;
};
