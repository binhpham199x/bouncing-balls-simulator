#include "BaseController.h"
#include <QDebug>
#include <QGraphicsItem>

BaseController::BaseController(BaseView* view, QObject* parent)
    : QObject(parent), m_view(view) {
  this->createCircleWallAtCenter(350);
  this->createExitAreaAtCenter(500);
  this->createBall();

  int FPS = 60;
  int timePerFrame = 1000 / FPS;

  QTimer* timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &BaseController::update);
  timer->start(timePerFrame);
}

void BaseController::createBall() {
  QPointF pos = m_circleWall->pos();
  Ball* ball = new Ball(pos, QPointF(500, 0));
  m_balls.push_back(ball);
  m_view->addGraphicsItem(ball);
}

void BaseController::createCircleWallAtCenter(qreal radius) {
  QPointF center = m_view->getCenterPoint();

  CircleWall* circleWall = new CircleWall(center, radius);
  m_view->addGraphicsItem(circleWall);
  m_circleWall = circleWall;
}

void BaseController::createExitAreaAtCenter(qreal length) {
  QPointF center = m_view->getCenterPoint();

  qreal factor = 0.5;
  qreal rotateSpeed = M_PI / (180 * factor);
  ExitArea* exitArea = new ExitArea(center, length, rotateSpeed);
  m_view->addGraphicsItem(exitArea);
  m_exitArea = exitArea;
}

void BaseController::spawnBallsOnBallExit(int numOfBalls) {
  for (int i = 0; i < numOfBalls; i++) {
    this->createBall();
  }
}

bool BaseController::doesBallCollideCircleWall(const Ball* ball) const {
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

  if (m_exitArea->getRotateSpeed() != 0)
    ballNewVelocity -= t * m_exitArea->getRotateSpeed();

  return ballNewVelocity;
}

bool BaseController::isBallInExitArea(Ball* ball) const {
  qreal twoPi = 2.0 * M_PI;
  qreal startAngle = m_exitArea->getStartAngle();
  qreal endAngle = m_exitArea->getEndAngle();

  QPointF ballPos = ball->pos();
  QPointF circleCenter = m_circleWall->pos();

  qreal dx = ballPos.x() - circleCenter.x();
  qreal dy = ballPos.y() - circleCenter.y();
  qreal ballAngle = qAtan2(dy, dx);

  if (ballAngle < 0)
    ballAngle += twoPi;

  if (startAngle < endAngle) {
    return (startAngle < ballAngle && ballAngle < endAngle);
  } else {
    return (startAngle < ballAngle || ballAngle < endAngle);
  }
}

void BaseController::correctBallPositionOnWallCollide(Ball* ball) {
  // d is radius vector of circle wall
  QPointF d = ball->pos() - m_circleWall->pos();
  qreal dLength = std::hypot(d.x(), d.y());

  QPointF dUnit = d / dLength;

  QPointF ballPos = m_circleWall->pos() +
                    dUnit * (m_circleWall->getRadius() - ball->getRadius());
  ball->setPos(ballPos);
}

void BaseController::handleBallWallCollide(Ball* ball) {
  QPointF ballNewVelocity = this->calculateNewBallVelocity(ball);

  ball->setVelocity(ballNewVelocity);
}

bool BaseController::isBallOutScreen(Ball* ball) const {
  qreal screenWidth = m_view->getScene()->width();
  qreal screenHeight = m_view->getScene()->height();
  qreal bX = ball->x();
  qreal bY = ball->y();
  qreal bR = ball->getRadius();

  return (bX - bR < 0 || bX + bR > screenWidth || bY - bR < 0 ||
          bY + bR > screenHeight);
}

void BaseController::updateSimulatorState() {
  qreal gravityFactor = 0.1;
  QPointF gravity = {0, gravityFactor * 1};
  std::list<Ball*> toRemove;

  for (Ball* ball : m_balls) {
    ball->update(gravity);

    if (this->isBallOutScreen(ball)) {
      toRemove.push_back(ball);
      continue;
    }

    if (!this->doesBallCollideCircleWall(ball)) {
      continue;
    }
    if (this->isBallInExitArea(ball)) {
      continue;
    }

    this->correctBallPositionOnWallCollide(ball);
    QPointF ballNewVelocity = this->calculateNewBallVelocity(ball);

    ball->setVelocity(ballNewVelocity);
  }

  int numOfBallsExit = toRemove.size();

  if (numOfBallsExit > 0) {
    for (Ball* ball : toRemove) {
      m_balls.remove(ball);
      m_view->getScene()->removeItem(ball);
      delete ball;
    }

    for (int i = 0; i < numOfBallsExit; i++) {
      this->spawnBallsOnBallExit(2);
    }
  }

  if (m_exitArea->getRotateSpeed() != 0)
    m_exitArea->rotate();
}

void BaseController::update() {
  this->updateSimulatorState();
  m_view->render();
}
