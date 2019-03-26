// SceneIterator.cpp

#include "GraphicsSceneImp.hpp"
#include "SceneIteratorImp.hpp"

namespace KaliLaska {
SceneIterator::SceneIterator(std::shared_ptr<SceneIteratorImp> imp)
    : imp_{std::move(imp)} {
}

SceneIterator::~SceneIterator() {
}

SceneIterator::SceneIterator(const SceneIterator &rhs)
    : imp_{rhs.imp_->copyItSelf()} {
}

SceneIterator &SceneIterator::operator=(const SceneIterator &rhs) {
  imp_ = rhs.imp_->copyItSelf();
  return *this;
}

GraphicsItem *SceneIterator::operator*() const {
  return imp_->operator*();
}

GraphicsItem *SceneIterator::operator->() const {
  return imp_->operator->();
}

SceneIterator &SceneIterator::operator++() {
  imp_->operator++();
  return *this;
}

SceneIterator &SceneIterator::operator++(int) {
  imp_->operator++();
  return *this;
}

bool SceneIterator::operator==(const SceneIterator &rhs) {
  return imp_ == rhs.imp_;
}

bool SceneIterator::operator!=(const SceneIterator &rhs) {
  return imp_ != rhs.imp_;
}

SceneIteratorImp *SceneIterator::imp() const {
  return imp_.get();
}

std::unique_ptr<SceneIterator> SceneIterator::copyItSelf() const {
  return std::make_unique<SceneIterator>(*this);
}
} // namespace KaliLaska
