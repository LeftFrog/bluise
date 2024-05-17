#include "CoverDelegate.h"
#include <QPainter>
#include <QPainterPath>

void CoverDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
  if (index.isValid()) {
    QRect rect = option.rect;
    QPixmap pixmap = index.data(Qt::UserRole).value<QPixmap>();
    QPainterPath path;
    path.addRoundedRect(rect, 5, 5);
    painter->setClipPath(path);
    painter->setPen(Qt::NoPen);
    if(pixmap.isNull()) {
      painter->drawRect(rect);
    } else {
      painter->drawPixmap(rect, pixmap);
    }
    if(option.state & QStyle::State_Selected) {
      painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
      QColor color = option.palette.highlight().color(); 
      color.setAlpha(15);
      painter->setBrush(color);
      painter->drawRect(rect);
    } 
  }
  // QStyledItemDelegate::paint(painter, option, index);
}

QSize CoverDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
  return size;
}