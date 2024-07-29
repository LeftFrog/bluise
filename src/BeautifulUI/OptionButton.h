//
// Created by Leonov Oleksandr on 2024-07-28.
//

#pragma once
#include <QAbstractButton>
#include <QLabel>

namespace BeautifulUi {
    class OptionButton : public QAbstractButton {
        Q_OBJECT

    public:
        OptionButton(const QString& text, QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent* event) override;

    private:
        QLabel* text;
    };
}





