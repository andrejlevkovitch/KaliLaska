// GraphicsSceneRTree.hpp

#include "GraphicsSceneRTree.hpp"
#include "KaliLaska/GraphicsItem.hpp"
#include "SceneIteratorRTree.hpp"
#include "debug.hpp"
#include <boost/geometry.hpp>
#include <boost/iterator/function_output_iterator.hpp>

namespace KaliLaska {
GraphicsSceneRTree::GraphicsSceneRTree() {
  boost::geometry::index::rtree<ValueType, Indexable>::const_iterator it;
}

GraphicsSceneRTree::~GraphicsSceneRTree() {
}

void GraphicsSceneRTree::addItem(std::shared_ptr<GraphicsItem> item) {
  // TODO implement
  UNUSED(item);
  // TODO use here std::move!!!
}

void GraphicsSceneRTree::removeItem(GraphicsItem *item) {
  if (auto found = std::find(this->begin(), this->end(), item);
      found != this->end()) {
    removeItem(found);
  }
}

SceneIterator GraphicsSceneRTree::begin() const {
  return SceneIterator{std::make_unique<SceneIteratorRTree>(tree_.begin())};
}

SceneIterator GraphicsSceneRTree::end() const {
  return SceneIterator{std::make_unique<SceneIteratorRTree>(tree_.end())};
}

void GraphicsSceneRTree::removeItem(const SceneIterator &iter) {
  auto *removeIter = reinterpret_cast<SceneIteratorRTree *>(iter.imp());
  auto  rtreeIter  = removeIter->imp();
  tree_.remove(rtreeIter, std::next(rtreeIter));
}

GraphicsItem *GraphicsSceneRTree::itemAt(const Point &pos) const {
  return tree_.qbegin(boost::geometry::index::contains(pos))->second.get();
}

std::list<GraphicsItem *> GraphicsSceneRTree::itemsAt(const Point &pos) const {
  std::list<GraphicsItem *> retval;
  tree_.query(boost::geometry::index::contains(pos),
              boost::make_function_output_iterator([&retval](const auto &val) {
                retval.push_back(val.second.get());
              }));
  return retval;
}
} // namespace KaliLaska
