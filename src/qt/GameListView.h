#pragma once
#include <QAbstractItemView>

class GameListView : public QAbstractItemView {
    Q_OBJECT
public:
    explicit GameListView(QWidget *parent = nullptr);
    virtual QModelIndex indexAt(const QPoint &point) const override;
    virtual void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) override;
    virtual QRect visualRect(const QModelIndex &index) const override;
protected:
    virtual int horizontalOffset() const override;
    virtual bool isIndexHidden(const QModelIndex &index) const override;
    virtual QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
    virtual void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) override;
    virtual int verticalOffset() const override;
    virtual QRegion visualRegionForSelection(const QItemSelection &selection) const override;
}