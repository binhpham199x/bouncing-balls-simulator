#include "CircleWall.h"

#include <QBrush>
#include <QPen>

CircleWall::CircleWall(const QPointF& center, qreal radius)
    : QGraphicsEllipseItem(-radius, -radius, radius * 2, radius * 2),
      m_radius(radius) {
  int BORDER_THICKNESS = 4;
  setPen(QPen(Qt::white, BORDER_THICKNESS));
  setBrush(Qt::NoBrush);
  setFlag(QGraphicsItem::ItemIsSelectable, false);
  setPos(center);

  setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
}

qreal CircleWall::getRadius() const {
  return m_radius;
}
