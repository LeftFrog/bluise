#pragma once
#include <QAbstractButton>
#include "../QtAwesome/QtAwesome/QtAwesome.h"

namespace BeautifulUi {

class BeautifulButton : public QAbstractButton {
  Q_OBJECT
public:
  explicit BeautifulButton(int _awesomeIcon = 0, QWidget *parent = nullptr);
  ~BeautifulButton();

  void setMenu(QMenu *menu);

  QSize sizeHint() const override;

protected:
  void paintEvent(QPaintEvent *event) override;
  void paintMenuButton(QPainter &painter, const QRect &rect);

  void enterEvent(QEnterEvent *event) override;
  void leaveEvent(QEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

  bool hovered = false;
protected slots:
  void setIcon(Qt::ColorScheme scheme);
private:
  int awesomeIcon;
  QMenu *menu;
  fa::QtAwesome *awesome;
};

}