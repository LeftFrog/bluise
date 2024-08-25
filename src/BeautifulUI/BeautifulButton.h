#pragma once
#include "AbstractBeautifulButton.h"
#include "../QtAwesome/QtAwesome/QtAwesome.h"

namespace BeautifulUi {
    class BeautifulButton : public AbstractBeautifulButton {
        Q_OBJECT

    public:
        explicit BeautifulButton(QWidget* parent = nullptr);
        ~BeautifulButton();

        void setMenu(QMenu* menu);

        QSize sizeHint() const override;

    protected:
        void paintEvent(QPaintEvent* event) override;
        void paintMenuButton(QPainter& painter, const QRect& rect);
        void mouseReleaseEvent(QMouseEvent* event) override;

    private:
        QMenu* menu;
    };
}
