#include "GameDelegate.h"

void GameDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect rect = option.rect;
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(option.palette.Button));
    painter->drawRoundedRect(rect, 10, 10);
    //painter->setPen(option.palette.Text);
    //painter->drawText(rect, Qt::AlignCenter, index.data().toString());
}