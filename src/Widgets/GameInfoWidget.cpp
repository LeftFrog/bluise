#include "GameInfoWidget.h"
#include <QtWidgets>
#include "EditGameWidget.h"
#include "../BeautifulUI/MenuButton.h"
#include "../BluiseCore/bluise.h"

QMenu* GameInfoWidget::createMenu() {
    QMenu* m = new QMenu();
    QAction* play = new QAction("Play", m);
    connect(play, &QAction::triggered, this, &GameInfoWidget::play);
    QAction* settings = new QAction("Settings", m);
    connect(settings, &QAction::triggered, this, &GameInfoWidget::settings);
    QAction* remove = new QAction("Remove", m);
    connect(remove, &QAction::triggered, this, &GameInfoWidget::removeGame);
    QAction* openWD = new QAction("Open game folder", m);
    connect(openWD, &QAction::triggered, this, &GameInfoWidget::openWorkingDirectory);

    m->QWidget::addAction(play);
    m->addSeparator();
    m->QWidget::addAction(settings);
    m->QWidget::addAction(openWD);
    m->QWidget::addAction(remove);
    return m;
}

GameInfoWidget::GameInfoWidget(QWidget* parent) : QWidget(parent) {
    setFixedHeight(100);

    menu = createMenu();

    QVBoxLayout* VBL = new QVBoxLayout(this);
    VBL->setContentsMargins(20, 20, 10, 20);
    VBL->setSpacing(10);

    label = new QLabel(this);
    label->setWordWrap(true);
    QFont f(font());
    f.setPointSize(22);
    label->setFont(f);
    VBL->addWidget(label, 0, Qt::AlignTop);

    MenuButton* button = new MenuButton(menu, this);
    button->setText("Play");
    button->setMenu(menu);
    button->setFixedSize(100, 30);
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    VBL->addWidget(button, 0, Qt::AlignBottom);
    connect(button, &MenuButton::clicked, this, &GameInfoWidget::play);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addLayout(VBL);
    QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addItem(spacer);
    setLayout(layout);

    setBackgroundRole(QPalette::Midlight);
    setAutoFillBackground(true);
}

void GameInfoWidget::setGame(const QModelIndex& index) {
    game = index.data(Qt::UserRole + 1).value<const Game*>();
    if (game == nullptr) {
        qDebug() << "Game is null";
        return;
    }
    label->setText(game->getName());
    this->show();
}

void GameInfoWidget::play() {
    if (game->isDisabled()) {
        QMessageBox::critical(this, "Error", "This game is not available.");
    } else {
        game->execute();
    }
}

void GameInfoWidget::settings() {
    EditGameWidget* edit_widget = new EditGameWidget(game);
    edit_widget->show();
}


void GameInfoWidget::popupMenu() {
    menu->popup(QCursor::pos());
}

void GameInfoWidget::removeGame() {
    gameManager.removeGame(*game);
    emit removeSignal();
    hide();
}

void GameInfoWidget::openWorkingDirectory() {
    QDir dir(game->getWorkingDirectory());
    if (dir.exists() && game->getWorkingDirectory() != "/") {
        QDesktopServices::openUrl(QUrl::fromLocalFile(dir.absolutePath()));
    } else {
        QMessageBox::critical(this, "Error", "Game folder is not specified");
    }
}
