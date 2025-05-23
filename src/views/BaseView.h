#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
#include "models/Ball.h"

class BaseView {
 public:
  BaseView(QGraphicsScene* scene, QGraphicsView* view);
  void addGraphicsItem(QGraphicsItem* item);
  void render();
  QGraphicsScene* getScene() const;
  QPointF getCenterPoint() const;

 private:
  QGraphicsScene* m_scene;
  QGraphicsView* m_view;
};