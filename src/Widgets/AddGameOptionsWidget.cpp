//
// Created by Leonov Oleksandr on 8/24/24.
//

#include "AddGameOptionsWidget.h"
#include <QPainterPath>
#include <QVBoxLayout>
#include "../BeautifulUI/OptionButton.h"
#include "../BluiseCore/bluise.h"

AddGameOptionsWidget::AddGameOptionsWidget(QWidget* parent) : QWidget(parent) {
    BeautifulUi::OptionButton* addLocalInstalledGame = new BeautifulUi::OptionButton("Add a local installed game", "Add a game that is already installed on your computer");
    addLocalInstalledGame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    connect(addLocalInstalledGame, &BeautifulUi::OptionButton::clicked, this, &AddGameOptionsWidget::addLocalGame);
    iconHandler.registerButton(addLocalInstalledGame, fa::fa_folder_plus);
    addLocalInstalledGame->setIcon(iconHandler.getIcon(fa::fa_solid, fa::fa_folder_plus));
    addLocalInstalledGame->setFixedHeight(60);


    BeautifulUi::OptionButton* scanForGames = new BeautifulUi::OptionButton("Scan for games on the hard drive", "Scan for games that are installed on your computer");
    scanForGames->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    connect(scanForGames, &BeautifulUi::OptionButton::clicked, this, &AddGameOptionsWidget::scanForGames);
    iconHandler.registerButton(scanForGames, fa::fa_magnifying_glass);
    scanForGames->setIcon(iconHandler.getIcon(fa::fa_solid, fa::fa_magnifying_glass));
    scanForGames->setFixedHeight(60);

    QVBoxLayout* VBL = new QVBoxLayout();
    VBL->setContentsMargins(0, 0, 0, 0);
    VBL->setSpacing(0);
    VBL->addWidget(addLocalInstalledGame);
    VBL->addWidget(scanForGames);
    setLayout(VBL);
}

void AddGameOptionsWidget::paintEvent(QPaintEvent* event) {
    QPainterPath path;
    path.addRoundedRect(rect(), 5, 5);
    setMask(path.toFillPolygon().toPolygon());
    QWidget::paintEvent(event);
}
