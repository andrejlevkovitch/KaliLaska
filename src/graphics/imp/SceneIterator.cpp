// SceneIterator.cpp

#include "GraphicsSceneImp.hpp"
#include "SceneIteratorImp.hpp"

namespace KaliLaska {
GraphicsSceneImp::SceneIterator::SceneIterator(
    std::unique_ptr<SceneIteratorImp> imp)
    : imp_{std::move(imp)} {
}

GraphicsSceneImp::SceneIterator::SceneIterator(SceneIterator &&rhs)
    : imp_{std::move(rhs.imp_)} {
}

GraphicsSceneImp::SceneIterator &GraphicsSceneImp::SceneIterator::
                                 operator=(SceneIterator &&rhs) {
  imp_ = std::move(rhs.imp_);
  return *this;
}

GraphicsSceneImp::SceneIterator::~SceneIterator() {
}

GraphicsItem *GraphicsSceneImp::SceneIterator::operator*() const {
  return imp_->operator*();
}

GraphicsItem *GraphicsSceneImp::SceneIterator::operator->() const {
  return imp_->operator->();
}

GraphicsSceneImp::SceneIterator &GraphicsSceneImp::SceneIterator::operator++() {
  imp_->operator++();
  return *this;
}

GraphicsSceneImp::SceneIterator &GraphicsSceneImp::SceneIterator::
                                 operator++(int) {
  imp_->operator++();
  return *this;
}
} // namespace KaliLaska
