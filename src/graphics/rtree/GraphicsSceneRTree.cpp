// GraphicsSceneRTree.hpp

#include "GraphicsSceneRTree.hpp"
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

GraphicsSceneRTree::SceneIterator GraphicsSceneRTree::begin() const {
  return SceneIterator{std::make_unique<SceneIteratorRTree>(tree_.begin())};
}

GraphicsSceneRTree::SceneIterator GraphicsSceneRTree::end() const {
  return SceneIterator{std::make_unique<SceneIteratorRTree>(tree_.end())};
}

GraphicsItem *GraphicsSceneRTree::itemAt(const Point &pos) const {
  return tree_.qbegin(boost::geometry::index::contains(pos))->second;
}

std::list<GraphicsItem *> GraphicsSceneRTree::itemsAt(const Point &pos) const {
  std::list<GraphicsItem *> retval;
  tree_.query(boost::geometry::index::contains(pos),
              boost::make_function_output_iterator([&retval](const auto &val) {
                retval.push_back(val.second);
              }));
  return retval;
}
} // namespace KaliLaska
