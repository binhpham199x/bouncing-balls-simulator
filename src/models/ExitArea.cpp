#include "ExitArea.h"
#include <QBrush>
#include <QPen>
#include "cmath"

ExitArea::ExitArea(const QPointF& rotateCorner,
                   const qreal length,
                   const qreal rotateSpeed,
                   const qreal startAngle,
                   const qreal endAngle)
    : m_rotateCorner(rotateCorner),
      m_length(length),
      m_rotateSpeed(rotateSpeed),
      m_startAngle(startAngle),
      m_endAngle(endAngle) {
  QPolygonF triangle = this->calculateTriangle();
  setPolygon(triangle);

  setBrush(Qt::black);
  setPen(Qt::NoPen);
}
QPointF ExitArea::calculateStartCorner() const {
  return m_rotateCorner + QPointF(m_length * std::cos(m_startAngle),
                                  m_length * std::sin(m_startAngle));
}
QPointF ExitArea::calculateEndCorner() const {
  return m_rotateCorner + QPointF(m_length * std::cos(m_endAngle),
                                  m_length * std::sin(m_endAngle));
}

qreal ExitArea::getLength() const {
  return m_length;
}

qreal ExitArea::getRotateSpeed() const {
  return m_rotateSpeed;
}

void ExitArea::rotate() {
  m_startAngle += m_rotateSpeed;
  m_endAngle += m_rotateSpeed;
  this->normalizeAngle();
  QPolygonF triangle = this->calculateTriangle();
  setPolygon(triangle);
}

QPolygonF ExitArea::calculateTriangle() const {
  QPointF p1 = this->calculateStartCorner();
  QPointF p2 = this->calculateEndCorner();

  QPolygonF triangle;
  triangle << m_rotateCorner << p1 << p2;
  return triangle;
}

void ExitArea::normalizeAngle() {
  qreal twoPi = 2.0 * M_PI;
  m_startAngle = std::fmod(m_startAngle, 2.0 * M_PI);
  if (m_startAngle < 0)
    m_startAngle += twoPi;

  m_endAngle = std::fmod(m_endAngle, 2.0 * M_PI);
  if (m_endAngle < 0)
    m_endAngle += 2.0 * twoPi;

  if (m_startAngle < m_endAngle)
    m_endAngle += 2.0 * twoPi;
}

qreal ExitArea::getStartAngle() const {
  return m_startAngle;
}
qreal ExitArea::getEndAngle() const {
  return m_endAngle;
}