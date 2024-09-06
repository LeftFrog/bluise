//
// Created by Leonov Oleksandr on 8/24/24.
//

#include "AddGameOptionsWidget.h"
#include <QPainterPath>
#include <QVBoxLayout>
#include "../BeautifulUI/OptionButton.h"
#include "../BluiseCore/bluise.h"

AddGameOptionsWidget::AddGameOptionsWidget(QWidget* parent) : QWidget(parent) {
    auto* VBL = new QVBoxLayout();
    VBL->setContentsMargins(0, 0, 0, 0);
    VBL->setSpacing(0);
    VBL->addWidget(createOptionButton("Add a local installed game", "Add a sgame that is already installed on your computer", fa::fa_folder_plus, &AddGameOptionsWidget::addLocalGame));
    VBL->addWidget(createOptionButton("Scan for games on the hard drive", "Scan for games that are installed on your computer", fa::fa_magnifying_glass, &AddGameOptionsWidget::scanForGames));
    setLayout(VBL);
}

void AddGameOptionsWidget::paintEvent(QPaintEvent* event) {
    QPainterPath path;
    path.addRoundedRect(rect(), 5, 5);
    setMask(path.toFillPolygon().toPolygon());
    QWidget::paintEvent(event);
}

BeautifulUi::OptionButton* AddGameOptionsWidget::createOptionButton(const QString& text, const QString& description,
    int icon, void (AddGameOptionsWidget::*slot) ()) {
    auto* button = new BeautifulUi::OptionButton(text, description);
    connect(button, &BeautifulUi::OptionButton::clicked, this, slot);
    iconHandler.registerButton(button, icon);
    button->setIcon(iconHandler.getIcon(fa::fa_solid, icon));
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    button->setFixedHeight(60);
    return button;
}
