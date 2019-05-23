// ConstIterator.cpp

#include "KaliLaska/GraphicsScene.hpp"
#include "graphics/imp/GraphicsSceneImp.hpp"

namespace KaliLaska {
GraphicsScene::ConstIterator::~ConstIterator() {
}

GraphicsScene::ConstIterator::ConstIterator(std::unique_ptr<SceneIterator> imp)
    : imp_{std::move(imp)} {
}

GraphicsScene::ConstIterator::ConstIterator(const ConstIterator &rhs)
    : imp_{rhs.imp_->copyItSelf()} {
}

GraphicsScene::ConstIterator &GraphicsScene::ConstIterator::ConstIterator::
                              operator=(const ConstIterator &rhs) {
  imp_ = rhs.imp_->copyItSelf();
  return *this;
}

AbstractGraphicsItem *GraphicsScene::ConstIterator::operator*() const {
  if (imp_) {
    return imp_->operator*();
  }
  return nullptr;
}

AbstractGraphicsItem *GraphicsScene::ConstIterator::operator->() const {
  if (imp_) {
    return imp_->operator->();
  }
  return nullptr;
}

GraphicsScene::ConstIterator &GraphicsScene::ConstIterator::operator++() {
  if (imp_) {
    imp_->operator++();
  }
  return *this;
}

GraphicsScene::ConstIterator &GraphicsScene::ConstIterator::operator++(int) {
  if (imp_) {
    imp_->operator++();
  }
  return *this;
}

bool GraphicsScene::ConstIterator::operator==(const ConstIterator &rhs) const {
  if (*imp_ == *rhs.imp_) {
    return true;
  }
  return false;
}

bool GraphicsScene::ConstIterator::operator!=(const ConstIterator &rhs) const {
  return !(*this == rhs);
}
} // namespace KaliLaska
