#pragma once
#include <QtWidgets>

class AddGameWidget : public QWidget {
    Q_OBJECT

public:
    AddGameWidget(QWidget* parent = nullptr);

public slots:
    void addLocalGame();
    void scanForGames();

signals:
    void gameAdded();
    void closed();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    QStackedLayout* layout;
};
