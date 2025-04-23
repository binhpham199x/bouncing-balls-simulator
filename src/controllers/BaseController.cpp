#include "BaseController.h"
#include <QDebug>
#include <QGraphicsItem>

BaseController::BaseController(BaseView* view, QObject* parent)
    : QObject(parent), m_view(view) {
  this->createCircleWallAtCenter(350);
  this->createExitAreaAtCenter(500);
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

void BaseController::createCircleWallAtCenter(qreal radius) {
  QPointF center = m_view->getCenterPoint();
  
  CircleWall* circleWall = new CircleWall(center, radius);
  m_view->addGraphicsItem(circleWall);
  m_circleWall = circleWall;
}

void BaseController::createExitAreaAtCenter(qreal length){
  QPointF center = m_view->getCenterPoint();
  ExitArea* exitArea = new ExitArea(center, length);
  m_view->addGraphicsItem(exitArea);
  m_exitArea = exitArea;
}

bool BaseController::doesBallCollideCircleWall(const Ball* ball) {
  qreal ballRadius = ball->getRadius();
  qreal circleRadius = m_circleWall->getRadius();

  qreal distance = QLineF(ball->pos(), m_circleWall->pos()).length();

  return ((distance + ballRadius) > circleRadius);
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

void BaseController::correctBallPositionOnWallCollide(Ball* ball) {
  // d is radius vector of circle wall
  QPointF d = QPointF(ball->pos() - m_circleWall->pos());
  qreal dLength = QLineF(QPointF(0, 0), d).length();
  qDebug() << "dLength" << dLength;

  QPointF dUnit = d / dLength;
  qDebug() << "dunit" << dUnit;
  QPointF ballPos = m_circleWall->pos() + dUnit * (m_circleWall->getRadius() - ball->getRadius());
  ball->setPos(ballPos);
}

void BaseController::handleBallWallCollide(Ball* ball) {
  QPointF ballNewVelocity = this->calculateNewBallVelocity(ball);
  ball->setVelocity(ballNewVelocity);
}

void BaseController::updateSimulatorState() {
  qreal gravityFactor = 1;
  QPointF gravity = {0, gravityFactor * 1};

  for (Ball* ball : m_balls) {
    ball->update(gravity);

    if (this->doesBallCollideCircleWall(ball)) {
      this->handleBallWallCollide(ball);
      this->correctBallPositionOnWallCollide(ball);
    }
  }
}

void BaseController::update() {
  this->updateSimulatorState();
  m_view->render();
}


BaseController::~BaseController(){

}