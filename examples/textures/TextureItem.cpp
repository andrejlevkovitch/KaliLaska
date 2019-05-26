// TextureItem.cpp

#include "TextureItem.hpp"
#include "KaliLaska/GraphicsScene.hpp"
#include "KaliLaska/Picture.hpp"
#include "KaliLaska/SceneMousePressEvent.hpp"
#include "KaliLaska/SceneMouseReleaseEvent.hpp"
#include <iostream>

TextureItem::TextureItem(const std::filesystem::path &file)
    : shape_{{0, 0}, {0, 60}, {80, 60}, {80, 0}, {0, 0}}
    , texture_{KaliLaska::Picture{file}} {
}

TextureItem::TextureItem(const std::filesystem::path &file,
                         const KaliLaska::Box &       box)
    : shape_{{0, 0}, {0, 60}, {80, 60}, {80, 0}, {0, 0}}
    , texture_{KaliLaska::Picture{file}, box} {
}

KaliLaska::Ring TextureItem::shape() const {
  return shape_;
}

void TextureItem::render(KaliLaska::GL::Renderer *renderer) const {
  if (cache_) {
    renderer->render(cache_, matrix(), texture_);
  } else {
    cache_ = renderer->render(shape_, matrix(), texture_);
  }
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
