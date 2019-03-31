// ExampleItem.cpp

#include "ExampleItem.hpp"
#include "KaliLaska/SceneMouseMoveEvent.hpp"
#include "KaliLaska/SceneMousePressEvent.hpp"
#include "KaliLaska/SceneMouseReleaseEvent.hpp"
#include "KaliLaska/opengl.hpp"
#include <boost/geometry.hpp>
#include <iostream>

namespace bg = boost::geometry;

ExampleItem::ExampleItem(const KaliLaska::Color &color)
    : color_{color} {
}

KaliLaska::Box ExampleItem::boundingBox() const {
  return {{0, 0}, {30, 30}};
}

void ExampleItem::render() const {
  auto box    = boundingBox();
  auto curPos = pos();
  bg::strategy::transform::translate_transformer<float, 2, 2> translate{
      bg::get<0>(curPos), bg::get<1>(curPos)};
  bg::transform(box, box, translate);
  KaliLaska::GL::Renderer::render(box, color_);
}

void ExampleItem::update() {
  // KaliLaska::PointF newPos = pos();
  // bg::add_point(newPos, KaliLaska::PointF{0.5, 0.5});
  // setPos(newPos);
}

void ExampleItem::mouseMoveEvent(KaliLaska::SceneMouseMoveEvent *event) {
  std::cout << "move event\n";
  event->accept();
}

void ExampleItem::mousePressEvent(KaliLaska::SceneMousePressEvent *event) {
  std::cout << "press event\n";
  event->accept();
}

void ExampleItem::mouseReleaseEvent(KaliLaska::SceneMouseReleaseEvent *event) {
  std::cout << "release event\n";
  event->accept();
}
