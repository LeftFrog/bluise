//
// Created by Leonov Oleksandr on 2024-07-28.
//

#pragma once
#include "AbstractBeautifulButton.h"
#include <QLabel>

namespace BeautifulUi {
    class OptionButton : public AbstractBeautifulButton {
        Q_OBJECT

    public:
        OptionButton(const QString& text, QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent* event) override;

    private:
        QString text;
        int iconMargin = 10;
    };
}





