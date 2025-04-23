#pragma once

#include <QObject>
#include <QTimer>
#include <vector>
#include "models/Ball.h"
#include "models/CircleWall.h"
#include "models/ExitArea.h"
#include "views/BaseView.h"

class BaseController : public QObject {
  Q_OBJECT
 public:
  explicit BaseController(BaseView* view, QObject* parent = nullptr);
  void updateSimulatorState();

 private:
  void createBall(qreal x, qreal y, qreal radius);
  void createCircleWallAtCenter(qreal radius);
  void createExitAreaAtCenter(qreal length);
  
  bool doesBallCollideCircleWall(const Ball* ball) const;
  QPointF calculateNewBallVelocity(const Ball* ball);
  void correctBallPositionOnWallCollide(Ball* ball);
  void handleBallWallCollide(Ball* ball);
  bool isBallInExitArea(Ball* ball) const;

 public slots:
  void update();

 private:
  BaseView* m_view;
  std::vector<Ball*> m_balls;
  CircleWall* m_circleWall;
  ExitArea* m_exitArea;
};