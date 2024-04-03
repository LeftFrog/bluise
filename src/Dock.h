#pragma once
#include <QQuickItem>
#include <QQuickWidget>

class Dock : public QQuickWidget {
  Q_OBJECT
public:
  Dock(QWidget *parent = nullptr);
signals:
  void added();
  void sort(const QString &order);
  void filter(const QString &filter, bool checked);

protected:
  virtual void resizeEvent(QResizeEvent *event) override;
public slots:
  void addGame();
};