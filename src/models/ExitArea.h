#pragma once

#include <QGraphicsPolygonItem>

class ExitArea : public QGraphicsPolygonItem {
 public:
  ExitArea(const QPointF& center, const qreal length);

  qreal getLength() const;

 private:
  qreal m_length;
};