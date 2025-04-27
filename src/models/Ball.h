#pragma once

#include <QGraphicsEllipseItem>
#include <QPointF>

class Ball : public QGraphicsEllipseItem {
 public:
  Ball(const QPointF& pos);
  Ball(const QPointF& pos, const QPointF& vel);
  Ball(const QPointF& pos, const QPointF& vel, const qreal radius);
  Ball(const QPointF& pos,
       const QPointF& vel,
       const qreal radius,
       const QColor& color);
  void update(const QPointF& gravity);
  qreal getRadius() const;
  QPointF getVelocity() const;
  void setVelocity(const QPointF& velocity);

 private:
  static QColor randomizeColor();
  QPointF randomizeStartVel();

 private:
  QPointF m_velocity;
  qreal m_radius;
};
