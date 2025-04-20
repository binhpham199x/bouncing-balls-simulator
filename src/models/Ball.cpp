#include "Ball.h"
#include <QBrush>

Ball::Ball(const QPointF& pos, const qreal radius)
    : QGraphicsEllipseItem(0, 0, radius, radius),m_radius(radius) {
  setBrush(Qt::blue);
  setPos(pos);
  
  // Prevent individual updates triggering repaints
  setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
}

void Ball::update(QPointF gravity) {
  m_velocity += gravity;
  QPointF newPos = pos() + m_velocity;

  setPos(newPos);
}