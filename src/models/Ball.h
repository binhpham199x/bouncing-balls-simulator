#pragma once

#include <QGraphicsEllipseItem>
#include <QPointF>

class Ball : public QGraphicsEllipseItem {
 public:
  Ball(const QPointF& pos, const qreal radius);
  void update(QPointF gravity);

 private:
  QPointF m_velocity = {0, 0};
  qreal m_radius;
};
