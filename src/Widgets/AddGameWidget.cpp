#include "AddGameWidget.h"
#include "AddLocalInstalledGameWidget.h"
#include "ScanForGamesWidget.h"
#include "../BeautifulUI/OptionButton.h"
#include <QTimer>

AddGameWidget::AddGameWidget(QWidget* parent) : QWidget(parent) {
    layout = new QStackedLayout();

    BeautifulUi::OptionButton* addLocalInstalledGame = new BeautifulUi::OptionButton("Add a local installed game");
    addLocalInstalledGame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    connect(addLocalInstalledGame, &BeautifulUi::OptionButton::clicked, this, &AddGameWidget::addLocalGame);

    BeautifulUi::OptionButton* scanForGames = new BeautifulUi::OptionButton("Scan for games on the hard drive");
    scanForGames->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    connect(scanForGames, &BeautifulUi::OptionButton::clicked, this, &AddGameWidget::scanForGames);

    QVBoxLayout* VBL = new QVBoxLayout();
    VBL->setContentsMargins(5, 5, 5, 5);
    VBL->setSpacing(0);
    VBL->addWidget(addLocalInstalledGame);
    VBL->addWidget(scanForGames);

    QWidget* options = new QWidget();
    options->setLayout(VBL);
    layout->addWidget(options);

    setLayout(layout);
}

void AddGameWidget::addLocalGame() {
    AddLocalInstalledGameWidget* wid = new AddLocalInstalledGameWidget();
    resize(700, 689);
    connect(wid, &AddLocalInstalledGameWidget::closed, this, &AddGameWidget::close);
    layout->addWidget(wid);
    layout->setCurrentIndex(1);
}

void AddGameWidget::scanForGames() {
    ScanForGamesWidget* wid = new ScanForGamesWidget();
    connect(wid, &ScanForGamesWidget::closed, this, &AddGameWidget::close);
    connect(wid, &ScanForGamesWidget::gameAdded, this, &AddGameWidget::gameAdded);
    layout->addWidget(wid);
    layout->setCurrentIndex(1);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, wid, &ScanForGamesWidget::scan);
    timer->setSingleShot(true); // Run only once
    timer->start(10);
}

void AddGameWidget::closeEvent(QCloseEvent* event) {
    QWidget::closeEvent(event);
}
