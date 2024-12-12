#include "AddGameWidget.h"
#include "AddLocalInstalledGameWidget.h"
#include "ScanForGamesWidget.h"
#include "../BeautifulUI/OptionButton.h"
#include "../BluiseCore/bluise.h"
#include <QTimer>

#include "AddGameOptionsWidget.h"


AddGameWidget::AddGameWidget(QWidget* parent) : QWidget(parent) {
    layout = new QStackedLayout();

    QLabel* lbl = new QLabel("Add games to your library");
    lbl->setStyleSheet("font-size: 16px; font-weight: bold;");
    lbl->setAlignment(Qt::AlignCenter);

    AddGameOptionsWidget* optionsWidget = new AddGameOptionsWidget();

    connect(optionsWidget, &AddGameOptionsWidget::addLocalGame, this, &AddGameWidget::addLocalGame);
    connect(optionsWidget, &AddGameOptionsWidget::scanForGames, this, &AddGameWidget::scanForGames);

    QVBoxLayout* VBL = new QVBoxLayout();
    VBL->setContentsMargins(10, 10, 10, 10);
    VBL->setSpacing(0);
    VBL->addSpacing(10);
    VBL->addWidget(lbl, 0, Qt::AlignCenter);
    VBL->addSpacing(20);
    VBL->addWidget(optionsWidget, 0, Qt::AlignTop);
    VBL->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

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
    emit closed();
    QWidget::closeEvent(event);
}
