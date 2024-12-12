#include "ScanForGamesWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "../BluiseCore/bluise.h"
#include "../BluiseCore/Game.h"

ScanForGamesWidget::ScanForGamesWidget(QWidget* parent) : QWidget(parent) {
    label = new QLabel("Scanning for games...");
    label->setAlignment(Qt::AlignCenter);

    progress = new QProgressBar();
    progress->setRange(0, 0);
    progress->setAlignment(Qt::AlignCenter);

    scanner = new GameScanner(this);
    connect(scanner, &GameScanner::gamesFound, this, &ScanForGamesWidget::gamesFound);
    text = new QTextEdit();

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(progress);
    setLayout(layout);
}

void ScanForGamesWidget::scan() {
    scanner->scanDirectory("/Applications");
}

void ScanForGamesWidget::closeEvent(QCloseEvent* event) {
    emit closed();
    QWidget::closeEvent(event);
}

void ScanForGamesWidget::gamesFound(const QList<Game>& games) {
    layout()->removeWidget(progress);
    progress->deleteLater();
    label->setText("Found games: ");

    text->setReadOnly(true);
    if (!games.empty()) {
        for (const auto& game : games) {
            text->append(game.getName());
        }
    } else {
        text->setText("No games found.");
        text->setAlignment(Qt::AlignCenter);
    }
    layout()->addWidget(text);

    auto* cancel = new QPushButton("Cancel");
    auto* add = new QPushButton("Add");
    add->setDefault(true);

    connect(cancel, &QPushButton::clicked, this, &ScanForGamesWidget::close);
    connect(add, &QPushButton::clicked, [this, games] {
        addGames(games);
        emit gameAdded();
        close();
    });

    auto* HBL = new QHBoxLayout;
    HBL->addWidget(cancel);
    HBL->addWidget(add);
    dynamic_cast<QVBoxLayout*>(layout())->addLayout(HBL);
}

void ScanForGamesWidget::addGames(const QList<Game>& games) {
    gameManager.addGames(games);
}
