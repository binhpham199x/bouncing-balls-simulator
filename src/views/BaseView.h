#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
#include "models/Ball.h"

class BaseView {
 public:
  BaseView(QGraphicsScene* scene, QGraphicsView* view);
  void addBall(Ball* ball);
  void addGraphicsItem(QGraphicsItem* item);
  void render();
  QGraphicsScene* getScene() const;

 private:
  QGraphicsScene* m_scene;
  QGraphicsView* m_view;
  std::vector<Ball*> m_balls;
};