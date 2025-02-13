#include "MainWindow.h"
#include "./ModelView/CoverDelegate.h"
#include "./BluiseCore/bluise.h"
#include "./ModelView/GameProxyModel.h"
#include "Widgets/AddGameWidget.h"

#ifdef Q_OS_MAC
extern void configureMacWindow(QWidget* qtWindow);
#endif

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    gameManager.loadGames(DOCS + "games.json");
    iconHandler.initFontAwesome();

#ifdef Q_OS_MACOS
    QTimer::singleShot(500, [this]() {
        configureMacWindow(this);
        setUnifiedTitleAndToolBarOnMac(true);
    });
#endif

    // setWindowTitle("Bluise");
    resize(1900, 800);

    initMenuBar();
    initToolBar();
    initListView();

    setWindowIcon(QIcon("/Users/leftfrog/Projects/bluise/res/1024-mac.png"));

    setCentralWidget(createSplitter());
    addToolBar(Qt::TopToolBarArea, toolbar);
    toolbar->setMovable(false);
}

MainWindow::~MainWindow() {
    gameManager.saveGames(DOCS + "games.json");
}

void MainWindow::handleMenus(QAction* action) {
    if (action->text() == "New Game") {
        addGame();
    }
}

void MainWindow::addGame() {
    AddGameWidget* addWidget = new AddGameWidget();
    addWidget->show();
    connect(addWidget, &AddGameWidget::closed, addWidget, &AddGameWidget::deleteLater);
}

void MainWindow::initMenuBar() {
    menuBar = new QMenuBar();
    QMenu* fileMenu = menuBar->addMenu("&File");
    fileMenu->addAction("New Game");
    connect(fileMenu, &QMenu::triggered, this, &MainWindow::handleMenus);
    setMenuBar(menuBar);
}

void MainWindow::initListView() {
    list = new QListView();
    list->setModel(gameManager.gameProxyModel);
    list->setViewMode(QListView::IconMode);
    list->setItemDelegate(new CoverDelegate(QSize(265 / 1.5, 376 / 1.5)));
    list->setResizeMode(QListView::Adjust);
    list->setUniformItemSizes(true);
    list->setSizeAdjustPolicy(QListView::AdjustToContentsOnFirstShow);
    list->setWrapping(true);
    list->setSpacing(15);
    list->setFlow(QListView::LeftToRight);
}

void MainWindow::initToolBar() {
    toolbar = new ToolBar(this);
    connect(toolbar, &ToolBar::addGame, this, &MainWindow::addGame);
    connect(toolbar, &ToolBar::setFilter, gameManager.gameProxyModel, &GameProxyModel::setFilterExp);
    connect(toolbar, &ToolBar::setName, gameManager.gameProxyModel, &GameProxyModel::setNameExp);
    connect(toolbar, &ToolBar::setSort, gameManager.gameProxyModel, &QSortFilterProxyModel::setSortRole);
}

GameInfoWidget* MainWindow::createGameInfoWidget() {
    GameInfoWidget* info = new GameInfoWidget();
    info->hide();
    connect(list, &QListView::clicked, info, &GameInfoWidget::setGame);
    return info;
}

QSplitter* MainWindow::createSplitter() {
    QSplitter* splitter = new QSplitter(Qt::Vertical, this);
    splitter->addWidget(list);
    splitter->addWidget(createGameInfoWidget());
    splitter->setHandleWidth(2);
    splitter->setCollapsible(1, false);
    return  splitter;
}
