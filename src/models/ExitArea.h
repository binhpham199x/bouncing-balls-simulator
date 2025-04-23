#pragma once

#include <QGraphicsPolygonItem>

class ExitArea : public QGraphicsPolygonItem {
 public:
  ExitArea(const QPointF& center,
           const qreal length,
           const qreal rotateSpeed = M_PI / 180,
           const qreal startAngle = 0.0,
           const qreal endAngle = M_PI / 3.0);

  qreal getLength() const;
  qreal getRotateSpeed() const;
  void rotate();
  qreal getStartAngle() const;
  qreal getEndAngle() const;

 private:
 QPointF calculateStartCorner() const;
 QPointF calculateEndCorner() const;
 void normalizeAngle();
 QPolygonF calculateTriangle () const;
 
 private:
  qreal m_length;
  qreal m_rotateSpeed;
  QPointF m_rotateCorner;
  qreal m_startAngle;
  qreal m_endAngle;
};