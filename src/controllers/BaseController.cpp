#include "BaseController.h"
#include <QDebug>
#include <QGraphicsItem>

BaseController::BaseController(BaseView* view, QObject* parent)
    : QObject(parent), m_view(view) {
  this->createCircleWall(350);

  this->createBall(400, 100, 20);

  QTimer* timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &BaseController::update);
  timer->start(16);
}

void BaseController::createBall(qreal x, qreal y, qreal radius) {
  QPointF pos = {x, y};
  Ball* ball = new Ball(pos, radius);
  m_balls.push_back(ball);
  m_view->addBall(ball);
}

void BaseController::createCircleWall(qreal radius) {
  qreal sceneWidth = m_view->getScene()->width();
  qreal sceneHeight = m_view->getScene()->height();

  QPointF center = {(sceneWidth / 2), (sceneHeight / 2)};

  CircleWall* circleWall = new CircleWall(center, radius);
  m_view->addGraphicsItem(circleWall);
  m_circleWall = circleWall;
}

bool BaseController::doesBallCollideCircleWall(const Ball* ball) {
  qreal ballRadius = ball->getRadius();
  qreal circleRadius = m_circleWall->getRadius();

  qreal distance = QLineF(ball->pos(), m_circleWall->pos()).length();
  
  return ((distance + ballRadius) >= circleRadius);
}

QPointF BaseController::calculateNewBallVelocity(const Ball* ball) {
  // d is radius vector of circle wall
  QPointF d = ball->pos() - m_circleWall->pos();
  // t is normal vector of circle wall
  QPointF t = {d.y(), -d.x()};

  QPointF projectionVOnT = t * (QPointF::dotProduct(ball->getVelocity(), t) /
                                QPointF::dotProduct(t, t));

  QPointF ballNewVelocity = 2 * projectionVOnT - ball->getVelocity();
  return ballNewVelocity;
}

void BaseController::handleBallWallCollide(Ball* ball) {
  QPointF ballNewVelocity = this->calculateNewBallVelocity(ball);
  ball->setVelocity(ballNewVelocity);
}

void BaseController::updateSimulatorState() {
  qreal gravityFactor = 0.2;
  QPointF gravity = {0, gravityFactor * 1};

  for (Ball* ball : m_balls) {
    ball->update(gravity);

    if (this->doesBallCollideCircleWall(ball)) {
      this->handleBallWallCollide(ball);
    }
  }
}

void BaseController::update() {
  this->updateSimulatorState();
  m_view->render();
}
