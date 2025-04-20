#include "BaseController.h"
#include <QDebug>

BaseController::BaseController(BaseView* view, QObject* parent)
    : QObject(parent), m_view(view) {
  this->createBall(100, 20, 40);

  QTimer* timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &BaseController::update);
  timer->start(100);
}

void BaseController::createBall(qreal x, qreal y, qreal radius) {
  Ball* ball = new Ball({x, y}, radius);
  m_balls.push_back(ball);
  m_view->addBall(ball);
}

void BaseController::updateSimulatorState() {
  qreal gravityFactor = 0.05;
  QPointF gravity = {0, gravityFactor * 1};

  for (Ball* ball : m_balls) {
    ball->update(gravity);
  }
}

void BaseController::update() {
  this->updateSimulatorState();
  m_view->render();
}
