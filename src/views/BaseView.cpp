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

QPointF BaseView::getCenterPoint() const{
  qreal sceneWidth = this->m_scene->width();
  qreal sceneHeight = this->m_scene->height();

  QPointF center = {(sceneWidth / 2), (sceneHeight / 2)};

  return center;
}

void BaseView::addGraphicsItem(QGraphicsItem* item) {
  m_scene->addItem(item);
}

void BaseView::render() {
  m_view->viewport()->update();
}