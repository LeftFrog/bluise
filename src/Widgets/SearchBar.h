#pragma once
#include <QLineEdit>

class SearchBar : public QLineEdit {
public:
  SearchBar(QWidget *parent = nullptr);
private slots:
  void changeTheme(Qt::ColorScheme scheme);
};