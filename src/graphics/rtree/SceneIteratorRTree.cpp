// SceneIteratorRTree.cpp

#include "SceneIteratorRTree.hpp"

namespace KaliLaska {
SceneIteratorRTree::SceneIteratorRTree(
    const GraphicsSceneRTree::TreeType::const_iterator &it)
    : it_{it} {
}

SceneIteratorRTree::~SceneIteratorRTree() {
}

GraphicsItem *SceneIteratorRTree::operator*() const {
  return it_.operator*().second;
}

GraphicsItem *SceneIteratorRTree::operator->() const {
  return it_.operator->()->second;
}

SceneIteratorRTree &SceneIteratorRTree::operator++() {
  ++it_;
  return *this;
}

SceneIteratorRTree &SceneIteratorRTree::operator++(int) {
  ++it_;
  return *this;
}
} // namespace KaliLaska
