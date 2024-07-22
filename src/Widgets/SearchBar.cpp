#include "SearchBar.h"
#include <QApplication>
#include <QStyleHints>

SearchBar::SearchBar(QWidget* parent) : QLineEdit(parent) {
    setPlaceholderText(" Search game by name");
    setStyleSheet("QLineEdit { border-radius: 5px; }");
    connect(QApplication::styleHints(), &QStyleHints::colorSchemeChanged, this, &SearchBar::changeTheme);
}

void SearchBar::changeTheme(Qt::ColorScheme scheme) {
    setStyleSheet("QLineEdit { border-radius: 5px; }");
}
