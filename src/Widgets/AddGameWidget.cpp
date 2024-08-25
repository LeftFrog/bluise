#include "AddGameWidget.h"
#include "AddLocalInstalledGameWidget.h"
#include "ScanForGamesWidget.h"
#include "../BeautifulUI/OptionButton.h"
#include "../BluiseCore/bluise.h"
#include <QTimer>

#include "AddGameOptionsWidget.h"


AddGameWidget::AddGameWidget(QWidget* parent) : QWidget(parent) {
    layout = new QStackedLayout();

    AddGameOptionsWidget* optionsWidget = new AddGameOptionsWidget();

    QVBoxLayout* VBL = new QVBoxLayout();
    VBL->setContentsMargins(10, 10, 10, 10);
    VBL->setSpacing(0);
    VBL->addWidget(optionsWidget, 0, Qt::AlignTop);
    // VBL->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

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
