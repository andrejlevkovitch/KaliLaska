// SceneIteratorRTree.cpp

#include "SceneIteratorRTree.hpp"

namespace KaliLaska {
SceneIteratorRTree::SceneIteratorRTree(
    const GraphicsSceneRTree::TreeType::const_iterator &it)
    : it_{it} {
}

SceneIteratorRTree::~SceneIteratorRTree() {
}

AbstractGraphicsItem *SceneIteratorRTree::operator*() const {
  return it_.operator*().second.get();
}

AbstractGraphicsItem *SceneIteratorRTree::operator->() const {
  return it_.operator->()->second.get();
}

SceneIteratorRTree &SceneIteratorRTree::operator++() {
  ++it_;
  return *this;
}

SceneIteratorRTree &SceneIteratorRTree::operator++(int) {
  ++it_;
  return *this;
}

GraphicsSceneRTree::TreeType::const_iterator SceneIteratorRTree::imp() const {
  return it_;
}

bool SceneIteratorRTree::operator==(const SceneIteratorImp &rhs) const {
  try {
    const auto &rIter = dynamic_cast<const SceneIteratorRTree &>(rhs);
    if (it_ == rIter.it_) {
      return true;
    }
  } catch (std::bad_cast &) {
    throw;
  }
  return false;
}

bool SceneIteratorRTree::operator!=(const SceneIteratorImp &rhs) const {
  return !(*this == rhs);
}

std::unique_ptr<SceneIteratorImp> SceneIteratorRTree::copyItSelf() const {
  return std::make_unique<SceneIteratorRTree>(it_);
}
} // namespace KaliLaska
