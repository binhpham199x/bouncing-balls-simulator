#include "CircleWall.h"

#include <QBrush>
#include <QPen>

CircleWall::CircleWall(const QPointF& center, qreal radius)
    : QGraphicsEllipseItem(-radius, -radius, radius * 2, radius * 2) {
  int BORDER_THICKNESS = 4;
  setPen(QPen(Qt::white, BORDER_THICKNESS));
  setBrush(Qt::NoBrush);
  setFlag(QGraphicsItem::ItemIsSelectable, false);
  setPos(center);

  setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
}