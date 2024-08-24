#include "GameInfoWidget.h"
#include "./ui_GameInfoWidget.h"
#include <QtWidgets>
#include "EditGameWidget.h"
#include "../BluiseCore/bluise.h"

GameInfoWidget::GameInfoWidget(QWidget* parent) : QWidget(parent), ui(new Ui::GameInfoWidget) {
    ui->setupUi(this);
    setFixedHeight(100);

    menu = new QMenu();

    QAction* play = new QAction("Play", menu);
    connect(play, &QAction::triggered, this, &GameInfoWidget::play);
    QAction* settings = new QAction("Settings", menu);
    connect(settings, &QAction::triggered, this, &GameInfoWidget::settings);
    QAction* remove = new QAction("Remove", menu);
    connect(remove, &QAction::triggered, this, &GameInfoWidget::removeGame);
    QAction* openWD = new QAction("Open game folder", menu);
    connect(openWD, &QAction::triggered, this, &GameInfoWidget::openWorkingDirectory);

    menu->addAction(play);
    menu->addSeparator();
    menu->addAction(settings);
    menu->addAction(openWD);
    menu->addAction(remove);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &GameInfoWidget::play);
    connect(ui->pushButton, &QPushButton::clicked, this, &GameInfoWidget::popupMenu);

    ui->pushButton->setIcon(iconHandler.getIcon(fa::fa_solid, fa::fa_chevron_down));
    iconHandler.registerButton(ui->pushButton, fa::fa_chevron_down);

    setBackgroundRole(QPalette::Midlight);
    setAutoFillBackground(true);

    ui->label->setFont(QFont("Arial", 22));
}

GameInfoWidget::~GameInfoWidget() {
    delete ui;
}

void GameInfoWidget::setGame(const QModelIndex& index) {
    game = index.data(Qt::UserRole + 1).value<const Game*>();
    if (game == nullptr) {
        qDebug() << "Game is null";
        return;
    }
    ui->label->setText(game->getName());
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
        return;
    }
}
