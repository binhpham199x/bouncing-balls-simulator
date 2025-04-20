#pragma once

#include <QGraphicsEllipseItem>
#include <QPointF>

class Ball : public QGraphicsEllipseItem {
 public:
  Ball(const QPointF& pos, const qreal radius);
  void update(const QPointF& gravity);
  qreal getRadius() const;
  QPointF getVelocity() const;
  void setVelocity(const QPointF& velocity);

 private:
  QPointF m_velocity;
  qreal m_radius;
};
