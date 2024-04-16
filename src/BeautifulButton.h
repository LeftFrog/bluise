#pragma once
#include <QAbstractButton>

namespace BeautifulUi {

class BeautifulButton : public QAbstractButton {
  Q_OBJECT
public:
  explicit BeautifulButton(QWidget *parent = nullptr);
  ~BeautifulButton();

  QSize sizeHint() const override {
    return QSize(100, 50);
  }
protected:
  bool checked = false;
  void paintEvent(QPaintEvent *event) override;
};

}