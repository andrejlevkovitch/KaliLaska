// ExampleItem.cpp

#include "ExampleItem.hpp"
#include "KaliLaska/opengl.hpp"
#include <boost/geometry.hpp>

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
}
