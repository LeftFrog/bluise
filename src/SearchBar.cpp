#include "SearchBar.h"

SearchBar::SearchBar(QWidget *parent) : QLineEdit(parent) {
  setPlaceholderText(" Search game by name");
  setStyleSheet("QLineEdit { border-radius: 5px; }");
}