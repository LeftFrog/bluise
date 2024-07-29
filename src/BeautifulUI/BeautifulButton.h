#pragma once
#include "AbstractBeautifulButton.h"
#include "../QtAwesome/QtAwesome/QtAwesome.h"

namespace BeautifulUi {
    class BeautifulButton : public AbstractBeautifulButton {
        Q_OBJECT

    public:
        explicit BeautifulButton(int _awesomeIcon = 0, QWidget* parent = nullptr);
        ~BeautifulButton();

        void setMenu(QMenu* menu);

        QSize sizeHint() const override;

    protected:
        void paintEvent(QPaintEvent* event) override;
        void paintMenuButton(QPainter& painter, const QRect& rect);
        void mouseReleaseEvent(QMouseEvent* event) override;

    protected slots:
        void setIcon(Qt::ColorScheme scheme);

    private:
        int awesomeIcon;
        QMenu* menu;
        fa::QtAwesome* awesome;
    };
}
