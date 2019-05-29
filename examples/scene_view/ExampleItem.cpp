// ExampleItem.cpp

#include "ExampleItem.hpp"
#include "ExampleScene.hpp"
#include "KaliLaska/GraphicsScene.hpp"
#include "KaliLaska/SceneMouseMoveEvent.hpp"
#include "KaliLaska/SceneMousePressEvent.hpp"
#include "KaliLaska/SceneMouseReleaseEvent.hpp"
#include "KaliLaska/opengl.hpp"
#include "imgui.h"
#include <iostream>

namespace bg = boost::geometry;

ExampleItem::ExampleItem(const KaliLaska::Color &color) {
  color_ = color;
  setAnchor({15, 15});
  setZvalue(1);
}

KaliLaska::Box ExampleItem::boundingBox() const {
  return {{0, 0}, {30, 30}};
}

void ExampleItem::render(KaliLaska::GL::Renderer *renderer) const {
  if (cache_) {
    renderer->render(cache_, matrix(), color_);
  } else {
    cache_ = renderer->render(boundingBox(), matrix(), color_);
  }
}

void ExampleItem::update() {
  KaliLaska::PointF newPos = pos();
  bg::add_point(newPos, KaliLaska::PointF{0.5, 0.5});
  setPos(newPos);
}

void ExampleItem::mouseMoveEvent(KaliLaska::SceneMouseMoveEvent *event) {
  (void)event;
}

void ExampleItem::mousePressEvent(KaliLaska::SceneMousePressEvent *event) {
  scene()->grabbItem(this);
  event->accept();
  stackAbove();
}

void ExampleItem::mouseReleaseEvent(KaliLaska::SceneMouseReleaseEvent *event) {
  if (this == scene()->grabbedItem()) {
    scene()->grabbItem(nullptr);
    event->accept();
  }
}

KaliLaska::AbstractGraphicsItem::ItemType ExampleItem::type() const {
  return static_cast<KaliLaska::AbstractGraphicsItem::ItemType>(
      ExampleScene::ExampleItem);
}
