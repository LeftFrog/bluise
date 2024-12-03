#pragma once
#include "../BeautifulUI/BeautifulButton.h"
#include "../BeautifulUI/BeautifulButtonGroup.h"
#include "SearchBar.h"

class ToolBar : public QWidget {
    Q_OBJECT

public:
    explicit ToolBar(QWidget* parent = nullptr);

signals:
    void setSort(int role);
    void addGame();
    void setFilter(const QString& filer);
    void setName(const QString& name);

private:
    QMenu* createSortMenu();
    QMenu* createOptionsMenu();
    void setupButtons();
    void setupSearchBar();

    SearchBar* search;
    BeautifulUi::BeautifulButton* optionsButton;
    BeautifulUi::BeautifulButton* addButton;
    BeautifulUi::BeautifulButton* sortButton;

private slots:
    void filter(QAction* action);
    void sort(QAction* action);
    void openSettings();
};
