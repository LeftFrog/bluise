#pragma once
#include <QScrollArea>

class GameScrollArea : public QScrollArea {
  Q_OBJECT
public:
  GameScrollArea(QWidget *parent = nullptr);
signals:
  void added();
  void sort(const QString &order);
protected:
  virtual void resizeEvent(QResizeEvent *event) override;
};