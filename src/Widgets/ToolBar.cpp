#include "ToolBar.h"
#include <QMenu>
#include "../QtAwesome/QtAwesome/QtAwesome.h"
#include <QActionGroup>
#include "SettingsWidget.h"
#include "../BluiseCore/bluise.h"

ToolBar::ToolBar(QWidget* parent) : QToolBar(parent) {
    setFixedHeight(43);

    auto* awesome = new fa::QtAwesome;
    awesome->initFontAwesome();

    QWidget* container = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(container);

    QWidget* spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QWidget* spacer2 = new QWidget;
    spacer2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    setupButtons();
    setupSearchBar();

    layout->addWidget(addButton);
    layout->addWidget(spacer);
    layout->addWidget(search);
    layout->addWidget(spacer2);
    layout->addWidget(sortButton);
    layout->addWidget(optionsButton);
    layout->setContentsMargins(0, 0, 0, 0);
    //layout->setSizeConstraint(QLayout::SetMaximumSize);

    container->setContentsMargins(10, 6, 6, 10);
    setContentsMargins(0, 0, 0, 0);

    container->setLayout(layout);
    addWidget(container);
}

QMenu* ToolBar::createSortMenu() {
    QMenu* sortMenu = new QMenu();
    QActionGroup* sortGroup = new QActionGroup(sortMenu);

    QAction* nameSort = new QAction("Name");
    nameSort->setCheckable(true);
    nameSort->setChecked(true);
    sortMenu->addAction(nameSort);
    sortGroup->addAction(nameSort);

    QAction* yearSort = new QAction("Release year");
    yearSort->setCheckable(true);
    sortMenu->addAction(yearSort);
    sortGroup->addAction(yearSort);
    sortGroup->setExclusive(true);

    connect(sortMenu, &QMenu::triggered, this, &ToolBar::sort);
    return sortMenu;
}

QMenu* ToolBar::createOptionsMenu() {
    QMenu* optionsMenu = new QMenu();
    QAction* settings = new QAction("Settings");
    optionsMenu->addAction(settings);
    connect(settings, &QAction::triggered, this, &ToolBar::openSettings);

    QAction* installed = new QAction("Show unistalled");
    installed->setCheckable(true);
    installed->setChecked(true);

    QActionGroup* filters = new QActionGroup(optionsMenu);
    filters->setExclusive(false);
    filters->addAction(installed);

    connect(filters, &QActionGroup::triggered, this, &ToolBar::filter);
    optionsMenu->addAction(installed);
    return optionsMenu;
}

void ToolBar::setupButtons() {
    optionsButton = new BeautifulUi::BeautifulButton(this);
    optionsButton->setIcon(iconHandler.getIcon(fa::fa_solid, fa::fa_ellipsis));
    iconHandler.registerButton(optionsButton, fa::fa_ellipsis);
    optionsButton->setMenu(createOptionsMenu());
    optionsButton->setFixedSize(50, 30);

    sortButton = new BeautifulUi::BeautifulButton(this);
    sortButton->setIcon(iconHandler.getIcon(fa::fa_solid, fa::fa_sort));
    iconHandler.registerButton(sortButton, fa::fa_sort);
    sortButton->setMenu(createSortMenu());
    sortButton->setFixedSize(50, 30);

    addButton = new BeautifulUi::BeautifulButton(this);
    addButton->setIcon(iconHandler.getIcon(fa::fa_solid, fa::fa_plus));
    iconHandler.registerButton(addButton, fa::fa_plus);
    addButton->setCheckable(false);
    connect(addButton, &BeautifulUi::BeautifulButton::clicked, this, &ToolBar::addGame);
    addButton->setFixedSize(30, 30);
    addButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void ToolBar::setupSearchBar() {
    search = new SearchBar(this);
    search->setFixedHeight(25);
    search->setAlignment(Qt::AlignCenter);
    connect(search, &QLineEdit::textChanged, this, &ToolBar::setName);
}

void ToolBar::sort(QAction* action) {
    if (action->text() == "Release year") {
        emit setSort(Qt::UserRole + 2);
    } else if (action->text() == "Name") {
        emit setSort(Qt::DisplayRole);
    }
}

void ToolBar::openSettings() {
    SettingsWidget* settings = new SettingsWidget();
    settings->show();
}

void ToolBar::filter(QAction* action) {
    if (action->text() == "Show unistalled") {
        emit setFilter(action->isChecked() ? "" : "f");
    }
}
