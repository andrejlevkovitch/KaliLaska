// RingItem.cpp

#include "RingItem.hpp"
#include "ExampleScene.hpp"
#include "KaliLaska/GraphicsScene.hpp"
#include "KaliLaska/SceneMousePressEvent.hpp"
#include "KaliLaska/SceneMouseReleaseEvent.hpp"
#include "KaliLaska/opengl.hpp"
#include <boost/geometry.hpp>
#include <iostream>

namespace bg = boost::geometry;
namespace bq = boost::qvm;

RingItem::RingItem() {
  bg::read_wkt(
      "POLYGON((10 0, 10 10, 20 10, 20 30, 10 30, 10 40, 20 40, 20 50, 30 50, "
      "30 40, 40 40, 40 30, 30 30, 30 10, 40 10, 40 0, 10 0))",
      shape_);
  setAnchor(bg::return_centroid<KaliLaska::PointF>(boundingBox()));
  setZvalue(0);
}

void RingItem::update() {
  // if (scene() && scene()->grabbedItem() != this) {
  //  auto curpos = pos();
  //  bg::add_point(curpos, KaliLaska::PointF{1, 0.5});
  //  setPos(curpos);
  //}
}

void RingItem::render(KaliLaska::GL::Renderer *renderer) const {
  // if (cache_) {
  //  renderer->render(cache_, matrix(), KaliLaska::Color::Colors::Blue);
  //} else {
  /*cache_ =*/
  renderer->render(shape(), matrix(), KaliLaska::Color::Colors::Blue);
  //}
}

KaliLaska::Ring RingItem::shape() const {
  return shape_;
}

void RingItem::mousePressEvent(KaliLaska::SceneMousePressEvent *event) {
  KaliLaska::PointF clickPos;
  auto              inverted = bq::inverse(matrix());
  bg::strategy::transform::matrix_transformer<float, 2, 2> transformer{
      inverted};
  bg::transform(event->clickPos(), clickPos, transformer);
  if (bg::intersects(clickPos, shape_)) {
    scene()->grabbItem(this);
    event->accept();
  }
}

void RingItem::mouseReleaseEvent(KaliLaska::SceneMouseReleaseEvent *event) {
  if (this == scene()->grabbedItem()) {
    scene()->grabbItem(nullptr);
    event->accept();
  }
}

KaliLaska::GraphicsItem::ItemType RingItem::type() const {
  return static_cast<KaliLaska::GraphicsItem::ItemType>(ExampleScene::RingItem);
}
