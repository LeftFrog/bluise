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
        OptionButton(const QString& text, const QString& description = "", QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent* event) override;

    private:
        void paintText(QPainter& painter) const;

        QFont boldFont;

        QString text;
        QString description;

        int iconMargin = 10;
        int chevronMargin = 20;
    };
}





