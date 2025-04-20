#include "CircleWall.h"

#include <QPen>
#include <QBrush>

CircleWall::CircleWall(const QPointF& center, qreal radius)
    : QGraphicsEllipseItem(center.x() - radius,
                           center.y() - radius,
                           radius * 2,
                           radius * 2) {
  setPen(QPen(Qt::white, 4));
  setBrush(Qt::NoBrush);
  setFlag(QGraphicsItem::ItemIsSelectable, false);
}
