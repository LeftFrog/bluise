#pragma once 
#include <QQuickWidget>
#include <QQuickItem>

class Dock : public QQuickWidget {
  Q_OBJECT
public:
  Dock(QWidget *parent = nullptr);
signals:
  void added();
  void sort(const QString &order);
protected:
  virtual void resizeEvent(QResizeEvent *event) override;
public slots: 
  void addGame();
};