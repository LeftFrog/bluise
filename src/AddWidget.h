#pragma once
#include <QQuickItem>
#include <QQuickWidget>

class AddWidget : public QQuickWidget {
  Q_OBJECT
public:
  AddWidget(QWidget *parent = nullptr);
  virtual QSize sizeHint() const override { return QSize(50, 50);};
public slots:
  void add();
protected:
  virtual void resizeEvent(QResizeEvent *event) override;
};