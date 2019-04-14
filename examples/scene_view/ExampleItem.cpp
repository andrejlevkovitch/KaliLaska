// ExampleItem.cpp

#include "ExampleItem.hpp"
#include "ExampleScene.hpp"
#include "KaliLaska/GraphicsScene.hpp"
#include "KaliLaska/SceneMouseMoveEvent.hpp"
#include "KaliLaska/SceneMousePressEvent.hpp"
#include "KaliLaska/SceneMouseReleaseEvent.hpp"
#include "KaliLaska/opengl.hpp"
#include <iostream>

namespace bg = boost::geometry;

ExampleItem::ExampleItem(const KaliLaska::Color &color)
    : color_{color} {
  setAnchor({15, 15});
}

KaliLaska::Ring ExampleItem::shape() const {
  return {{0, 0}, {0, 30}, {30, 30}, {30, 0}, {0, 0}};
}

void ExampleItem::render(KaliLaska::GL::Renderer *renderer) const {
  auto box = boundingBox();

  renderer->render(box, color_, matrix());
}

void ExampleItem::update() {
  // KaliLaska::PointF newPos = pos();
  // bg::add_point(newPos, KaliLaska::PointF{0.5, 0.5});
  // setPos(newPos);
}

void ExampleItem::mouseMoveEvent(KaliLaska::SceneMouseMoveEvent *event) {
  (void)event;
}

void ExampleItem::mousePressEvent(KaliLaska::SceneMousePressEvent *event) {
  scene()->grabbItem(this);
  event->accept();
}

void ExampleItem::mouseReleaseEvent(KaliLaska::SceneMouseReleaseEvent *event) {
  if (this == scene()->grabbedItem()) {
    scene()->grabbItem(nullptr);
    event->accept();
  }
}

KaliLaska::GraphicsItem::ItemType ExampleItem::type() const {
  return static_cast<KaliLaska::GraphicsItem::ItemType>(
      ExampleScene::ExampleItem);
}
