#pragma once
#include <QAbstractButton>

namespace BeautifulUi {

class BeautifulButton : public QAbstractButton {
  Q_OBJECT
public:
  explicit BeautifulButton(QWidget *parent = nullptr);
  ~BeautifulButton();

  void setMenu(QMenu *menu);

  QSize sizeHint() const override;

protected:
  bool checked = false;
  void paintEvent(QPaintEvent *event) override;
  void paintMenuButton(QPainter &painter, const QRect &rect);
private:
  QMenu *menu;
};

}