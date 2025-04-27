#include "Ball.h"
#include <QBrush>
#include <QPen>
#include <QRandomGenerator>

Ball::Ball(const QPointF& pos) : Ball(pos, this->randomizeStartVel()) {}

Ball::Ball(const QPointF& pos, const QPointF& vel)
    : Ball(pos, vel, 10, this->randomizeColor()) {}

Ball::Ball(const QPointF& pos, const QPointF& vel, const qreal radius)
    : Ball(pos, vel, radius, this->randomizeColor()) {}

Ball::Ball(const QPointF& pos,
           const QPointF& vel,
           const qreal radius,
           const QColor& color)
    : QGraphicsEllipseItem(-radius, -radius, radius * 2, radius * 2),
      m_radius(radius),
      m_velocity(vel.x(), vel.y()) {
  setPen(Qt::NoPen);
  setBrush(QBrush(color));
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

QColor Ball::randomizeColor() {
  QRandomGenerator* rnd = QRandomGenerator::global();
  int r = rnd->bounded(256);
  int g = rnd->bounded(256);
  int b = rnd->bounded(256);
  return QColor(r, g, b);
}

QPointF Ball::randomizeStartVel() {
  QRandomGenerator* rnd = QRandomGenerator::global();
  qreal x = static_cast<qreal>(rnd->bounded(-5, 6));
  qreal y = static_cast<qreal>(rnd->bounded(-5, 6));
  return {x, y};
};