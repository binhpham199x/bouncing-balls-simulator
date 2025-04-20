#pragma once

#include <QGraphicsEllipseItem>

class CircleWall : public QGraphicsEllipseItem {
 public:
  CircleWall(const QPointF& center, qreal radius);
  qreal getRadius() const;
 private:
  qreal m_radius;
};