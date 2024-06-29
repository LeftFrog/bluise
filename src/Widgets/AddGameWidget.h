#pragma once
#include <QtWidgets>

class AddGameWidget : public QWidget {
  Q_OBJECT
public:
  AddGameWidget(QWidget* parent = nullptr);
public slots:
  void addLocalGame();
  void searchGames();
private:
  QStackedLayout* layout;
};