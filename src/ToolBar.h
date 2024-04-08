#pragma once
#include <QQuickWidget>

class ToolBar : public QQuickWidget {
  Q_OBJECT
public:
  ToolBar(QWidget *parent = nullptr);
protected:
  void resizeEvent(QResizeEvent *event) override;
};