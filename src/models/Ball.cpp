#include "Ball.h"
#include <QBrush>
#include <QPen>

Ball::Ball(const QPointF& pos, const qreal radius)
    : QGraphicsEllipseItem(-radius, -radius, radius * 2, radius * 2),
      m_radius(radius),
      m_velocity(0, 0) {
  setPen(Qt::NoPen);
  setBrush(Qt::red);
  setPos(pos);

  // Prevent individual updates triggering repaints
  setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
}

qreal Ball::getRadius() const {
  return m_radius;
}

QPointF Ball::getVelocity() const {
  return m_velocity;
};

void Ball::setVelocity(const QPointF& velocity) {
  m_velocity = velocity;
};

void Ball::update(const QPointF& gravity) {
  m_velocity += gravity;
  QPointF newPos = pos() + m_velocity;

  setPos(newPos);
}