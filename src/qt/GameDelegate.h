#pragma once
#include <QtWidgets>

class GameDelegate : public QStyledItemDelegate {
public:
    GameDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override { return QSize(200, 80); };
};