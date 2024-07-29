//
// Created by Leonov Oleksandr on 2024-07-29.
//

#pragma once
#include <QAbstractButton>

namespace BeautifulUi {
    class AbstractBeautifulButton : public QAbstractButton {
        Q_OBJECT

    public:
        AbstractBeautifulButton(QWidget* parent = nullptr);

    protected:
        void enterEvent(QEnterEvent* event) override;
        void leaveEvent(QEvent* event) override;
        bool hovered = false;
    };
}
