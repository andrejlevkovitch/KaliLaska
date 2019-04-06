// RingItem.cpp

#include "RingItem.hpp"
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
}

void RingItem::update() {
  // if (scene() && scene()->grabbedItem() != this) {
  //  auto curpos = pos();
  //  bg::add_point(curpos, KaliLaska::PointF{1, 0.5});
  //  setPos(curpos);
  //}
}

void RingItem::render() const {
  KaliLaska::GL::Renderer::render(shape_, KaliLaska::Color::Colors::Blue);
}

KaliLaska::Box RingItem::boundingBox() const {
  return {{0, 0}, {50, 50}};
}

void RingItem::mousePressEvent(KaliLaska::SceneMousePressEvent *event) {
  auto clickPos = event->clickPos();
  auto inverted = bq::inverse(matrix());
  bg::strategy::transform::matrix_transformer<float, 2, 2> transformer{
      inverted};
  bg::transform(clickPos, clickPos, transformer);
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
