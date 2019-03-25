// ConstIterator.cpp

#include "IteratorImp.hpp"
#include "KaliLaska/GraphicsScene.hpp"

namespace KaliLaska {
GraphicsScene::ConstIterator::~ConstIterator() {
}

GraphicsScene::ConstIterator::ConstIterator(std::unique_ptr<IteratorImp> imp)
    : imp_{std::move(imp)} {
}

GraphicsItem *GraphicsScene::ConstIterator::operator*() const {
  if (imp_) {
    return imp_->operator*();
  }
  return nullptr;
}

GraphicsItem *GraphicsScene::ConstIterator::operator->() const {
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
} // namespace KaliLaska
