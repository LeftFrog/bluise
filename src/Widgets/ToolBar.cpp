#include "ToolBar.h"
#include <QPushButton>
#include <QMenu>
#include "../QtAwesome/QtAwesome/QtAwesome.h"
#include <QActionGroup>

ToolBar::ToolBar(QWidget* parent) : QWidget(parent) {
    setFixedHeight(36);

    auto* awesome = new fa::QtAwesome;
    awesome->initFontAwesome();

    QWidget* spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    optionsButton = new BeautifulUi::BeautifulButton(fa::fa_ellipsis, this);
    QMenu* optionsMenu = new QMenu();
    optionsMenu->addAction("Options");
    QAction* installed = new QAction("Show unistalled");
    installed->setCheckable(true);
    installed->setChecked(true);
    QActionGroup* filters = new QActionGroup(optionsMenu);
    filters->setExclusive(false);
    filters->addAction(installed);
    connect(filters, &QActionGroup::triggered, this, &ToolBar::filter);
    optionsMenu->addAction(installed);

    optionsButton->setMenu(optionsMenu);

    sortButton = new BeautifulUi::BeautifulButton(fa::fa_sort, this);
    sortButton->setMenu(createSortMenu());

    search = new SearchBar(this);
    search->setGeometry(width() / 5, 4, width() / 5 * 3, height() - 4);

    addButton = new BeautifulUi::BeautifulButton(fa::fa_plus, this);
    addButton->setCheckable(false);
    connect(addButton, &BeautifulUi::BeautifulButton::clicked, this, &ToolBar::addGame);

    connect(search, &QLineEdit::textChanged, this, &ToolBar::setName);

    setContentsMargins(10, 6, 6, 10);
}

void ToolBar::resizeEvent(QResizeEvent* event) {
    optionsButton->setGeometry(width() - optionsButton->width() - contentsMargins().right(),
                               (height() - optionsButton->height()) / 2 + 1, optionsButton->width(),
                               optionsButton->height());
    sortButton->setGeometry(width() - sortButton->width() - contentsMargins().right() * 2 - optionsButton->width(),
                            (height() - sortButton->height()) / 2 + 1, sortButton->width(), sortButton->height());
    // group->setGeometry(sortButton->x()-15-group->width(), (height() - group->height())/2+1, group->width(), group->height());
    addButton->setGeometry(contentsMargins().left(), (height() - addButton->height()) / 2 + 1, 30, addButton->height());
    search->setGeometry(width() / 12 * 3, contentsMargins().top(), width() / 12 * 6, height() - 9);
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

void ToolBar::sort(QAction* action) {
    if (action->text() == "Release year") {
        emit setSort(Qt::UserRole + 2);
    } else if (action->text() == "Name") {
        emit setSort(Qt::DisplayRole);
    }
}

void ToolBar::filter(QAction* action) {
    if (action->text() == "Show unistalled") {
        emit setFilter(action->isChecked() ? "" : "f");
    }
}
