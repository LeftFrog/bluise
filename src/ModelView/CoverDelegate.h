#pragma once
#include <QStyledItemDelegate>

class CoverDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    CoverDelegate(QSize _size = QSize(265 / 2, 376 / 2), QObject* parent = nullptr) : QStyledItemDelegate(parent),
        size(_size) {
    }

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setSize(QSize _size) { size = _size; }

private:
    QSize size;
};
