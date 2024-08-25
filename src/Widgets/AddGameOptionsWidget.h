//
// Created by Leonov Oleksandr on 8/24/24.
//

#pragma once
#include <QWidget>

class AddGameOptionsWidget : public QWidget {
    Q_OBJECT

public:
    AddGameOptionsWidget(QWidget* parent = nullptr);

signals:
    void addLocalGame();
    void scanForGames();

protected:
    void paintEvent(QPaintEvent* event) override;

private:

};
