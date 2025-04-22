#include "BaseView.h"
#include "models/CircleWall.h"

BaseView::BaseView(QGraphicsScene* scene, QGraphicsView* view)
    : m_scene(scene), m_view(view) {
  // Disable automatic viewport updates
  m_view->setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
}

QGraphicsScene* BaseView::getScene() const {
  return m_scene;
}

void BaseView::addBall(Ball* ball) {
  m_balls.push_back(ball);
  m_scene->addItem(ball);
}

void BaseView::addGraphicsItem(QGraphicsItem* item) {
  m_scene->addItem(item);
}

void BaseView::render() {
  m_view->viewport()->update();
}