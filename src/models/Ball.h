#pragma once

#include <QGraphicsEllipseItem>
#include <QPointF>

class Ball : public QGraphicsEllipseItem {
 public:
  Ball(const QPointF& pos, const qreal radius);
  Ball(const QPointF& pos, const qreal radius, const QColor& color);
  void update(const QPointF& gravity);
  qreal getRadius() const;
  QPointF getVelocity() const;
  void setVelocity(const QPointF& velocity);

 private:
  QColor randomizeColor();

 private:
  QPointF m_velocity;
  qreal m_radius;
};
