#pragma once

#include <QObject>
#include <QTimer>
#include <vector>
#include "views/BaseView.h"

class BaseController : public QObject {
  Q_OBJECT
 public:
  explicit BaseController(BaseView* view, QObject* parent = nullptr);
  void updateSimulatorState();

 private:
  void createBall(qreal x, qreal y, qreal radius);
 public slots:
  void update();

 private:
  BaseView* m_view;
  std::vector<Ball*> m_balls;
};