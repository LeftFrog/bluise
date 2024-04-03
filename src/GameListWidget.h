#pragma once
#include "GameWidget.h"
#include <QtWidgets>

class GameListWidget : public QWidget {
  Q_OBJECT
public:
  QList<GameWidget *> game_widgets;
  GameListWidget(QWidget *parent = nullptr);
  enum Filter {
    NotInstalled = 0x0,
  };
  Q_DECLARE_FLAGS(Filters, Filter)
public slots:
  void added();
  void sortWidgets(const QString &order);
  void filter(const QString &filter);
private:
  Filters filters;
  QGridLayout *layout;
  void addWidgets();
  void init();
};

Q_DECLARE_OPERATORS_FOR_FLAGS(GameListWidget::Filters) 