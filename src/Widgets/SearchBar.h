#pragma once
#include <QLineEdit>

class SearchBar : public QLineEdit {
    Q_OBJECT

public:
    SearchBar(QWidget* parent = nullptr);

private slots:
    void changeTheme(Qt::ColorScheme scheme);
};
