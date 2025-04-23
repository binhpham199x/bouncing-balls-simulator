#include "ExitArea.h"
#include "cmath"
#include <QBrush>
#include <QPen>

ExitArea::ExitArea(const QPointF& center, const qreal length)
    : m_length(length) {
  qreal startAngle = 0.0;
  qreal endAngle = M_PI / 3.0;

  QPointF p1 = center + QPointF(length * std::cos(startAngle),
                                length * std::sin(startAngle));
  QPointF p2 = center + QPointF(length * std::cos(endAngle),
                                length * std::sin(endAngle));

  QPolygonF triangle;
  triangle << center << p1 << p2;
  setPolygon(triangle);
  setBrush(Qt::white); 
  setPen(Qt::NoPen);

}

qreal ExitArea::getLength() const {
  return m_length;
}