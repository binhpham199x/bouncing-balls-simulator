#include "BaseView.h"

BaseView::BaseView(QGraphicsScene* scene, QGraphicsView* view)
    : m_scene(scene), m_view(view) {
  // Disable automatic viewport updates
  m_view->setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
}

void BaseView::addBall(Ball* ball) {
  m_balls.push_back(ball);
  m_scene->addItem(ball);
}

void BaseView::render() {
  m_view->viewport()->update();
}