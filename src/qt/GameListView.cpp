#include "GameListView.h"

GameListView::GameListView(QAbstractItemModel *model, QWidget *parent ) : QListView(parent)
{
    setItemDelegate(new GameDelegate(this));
    setViewMode(QListView::IconMode);
    setMovement(QListView::Snap);
    setModel(model);
    setGridSize(QSize(200, 80));
}