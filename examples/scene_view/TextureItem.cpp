// TextureItem.cpp

#include "TextureItem.hpp"
#include "ExampleScene.hpp"
#include "KaliLaska/Picture.hpp"
#include "KaliLaska/SceneMousePressEvent.hpp"
#include "KaliLaska/SceneMouseReleaseEvent.hpp"
#include <boost/geometry.hpp>
#include <iostream>

namespace bg = boost::geometry;
namespace bq = boost::qvm;

TextureItem::TextureItem(const std::filesystem::path &file)
    : shape_{{0, 0}, {0, 60}, {80, 60}, {80, 0}, {0, 0}}
    , texture_{KaliLaska::Picture{file}} {
}

BaseItem::ItemType TextureItem::type() const {
  return static_cast<KaliLaska::GraphicsItem::ItemType>(
      ExampleScene::TextureItem);
}

KaliLaska::Ring TextureItem::shape() const {
  return shape_;
}

void TextureItem::render(KaliLaska::GL::Renderer *renderer) const {
  if (renderer->use("texture")) {
    if (cache_) {
      renderer->render(cache_, matrix(), texture_);
    } else {
      cache_ = renderer->render(shape_, matrix(), texture_);
    }
    renderer->use("default");
  }
}

void TextureItem::mousePressEvent(KaliLaska::SceneMousePressEvent *event) {
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

void TextureItem::mouseReleaseEvent(KaliLaska::SceneMouseReleaseEvent *event) {
  if (this == scene()->grabbedItem()) {
    scene()->grabbItem(nullptr);
    event->accept();
  }
}
