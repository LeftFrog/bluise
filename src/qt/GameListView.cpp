#include "GameListView.h"

GameListView::GameListView(QAbstractItemModel *model, QWidget *parent ) : QListView(parent)
{
    setViewMode(QListView::IconMode);
    setMovement(QListView::Snap);
    setModel(model);
    setGridSize(QSize(70, 70));
}