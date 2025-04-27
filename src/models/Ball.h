#pragma once

#include <QGraphicsEllipseItem>
#include <QPointF>

class Ball : public QGraphicsEllipseItem {
 public:
  Ball(const QPointF& pos,
       const QPointF& vel = QPoint(0, 0),
       const qreal radius = 10);
  Ball(const QPointF& pos,
       const QPointF& vel,
       const qreal radius,
       const QColor& color);
  void update(const QPointF& gravity);
  qreal getRadius() const;
  QPointF getVelocity() const;
  void setVelocity(const QPointF& velocity);

 private:
  QColor randomizeColor();
  QPointF randomizeStartVel();

 private:
  QPointF m_velocity;
  qreal m_radius;
};
