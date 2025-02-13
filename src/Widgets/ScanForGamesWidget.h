#pragma once
#include <QProgressBar>
#include <QTextEdit>
#include <QLabel>
#include "../BluiseCore/GameScanner.h"

class ScanForGamesWidget final : public QWidget {
    Q_OBJECT

public:
    explicit ScanForGamesWidget(QWidget* parent = nullptr);

signals:
    void closed();
    void gameAdded();

public slots:
    void scan();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void gamesFound(const QList<Game>& games);

private:
    void addGames(const QList<Game>& games);

    GameScanner* scanner;
    QLabel* label;
    QProgressBar* progress;
    QTextEdit* text;
};
