#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>
#include "controllers/BaseController.h"
#include "views/BaseView.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  int windowWidth = 1000;
  int windowHeight = 800;

  QGraphicsScene scene;
  scene.setSceneRect(0, 0, windowWidth, windowHeight);
  scene.setBackgroundBrush(Qt::black);

  QGraphicsView view(&scene);
  view.setRenderHint(QPainter::Antialiasing);

  view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  view.setFixedSize(windowWidth, windowHeight);

  view.show();

  BaseView ballView(&scene, &view);
  BaseController controller(&ballView);

  return a.exec();
}