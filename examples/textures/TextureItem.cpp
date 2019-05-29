// TextureItem.cpp

#include "TextureItem.hpp"
#include "KaliLaska/GraphicsScene.hpp"
#include "KaliLaska/Picture.hpp"
#include "KaliLaska/SceneMousePressEvent.hpp"
#include "KaliLaska/SceneMouseReleaseEvent.hpp"
#include <iostream>

TextureItem::TextureItem(const std::filesystem::path &file)
    : box_{{0, 0}, {80, 60}}
    , texture_{KaliLaska::Picture{file}} {
}

TextureItem::TextureItem(const std::filesystem::path &file,
                         const KaliLaska::Box &       box,
                         const KaliLaska::Ring &      ring)
    : box_{{-80, -60}, {80, 60}}
    , texture_{KaliLaska::Picture{file}, box, ring} {
}

KaliLaska::Box TextureItem::boundingBox() const {
  return box_;
}

void TextureItem::render(KaliLaska::GL::Renderer *renderer) const {
  // if (cache_) {
  //  renderer->render(cache_, matrix(), texture_);
  //} else {
  cache_ = renderer->render(boundingBox(), matrix(), texture_);
  //}
}

void TextureItem::mousePressEvent(KaliLaska::SceneMousePressEvent *event) {
  stackAbove();
  scene()->grabbItem(this);
  event->accept();
}

void TextureItem::mouseReleaseEvent(KaliLaska::SceneMouseReleaseEvent *event) {
  if (this == scene()->grabbedItem()) {
    scene()->grabbItem(nullptr);
    event->accept();
  }
}
