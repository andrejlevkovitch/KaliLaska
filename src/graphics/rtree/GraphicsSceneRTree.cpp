// GraphicsSceneRTree.hpp

#include "GraphicsSceneRTree.hpp"
#include "KaliLaska/GraphicsItem.hpp"
#include "SceneIteratorRTree.hpp"
#include "debug.hpp"
#include <boost/geometry.hpp>
#include <boost/iterator/function_output_iterator.hpp>

namespace bg = boost::geometry;

namespace KaliLaska {
GraphicsSceneRTree::GraphicsSceneRTree() {
  bg::index::rtree<ValueType, Indexable>::const_iterator it;
}

GraphicsSceneRTree::~GraphicsSceneRTree() {
}

void GraphicsSceneRTree::addItem(std::shared_ptr<GraphicsItem> item) {
  auto box = item->boundingBox();
  bg::strategy::transform::matrix_transformer<float, 2, 2> traslator{
      item->matrix()};
  bg::transform(box, box, traslator);
  tree_.insert(ValueType{std::move(box), std::move(item)});
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

GraphicsItem *GraphicsSceneRTree::itemAt(const PointF &pos,
                                         Spatials      spat) const {
  switch (spat) {
  case Spatials::Contains:
    if (auto iter = tree_.qbegin(bg::index::contains(pos));
        iter != tree_.qend()) {
      return iter->second.get();
    }
    break;
  case Spatials::Intersects:
    if (auto iter = tree_.qbegin(bg::index::intersects(pos));
        iter != tree_.qend()) {
      return iter->second.get();
    }
    break;
  case Spatials::Within:
    break;
  }
  return nullptr;
}

std::list<GraphicsItem *> GraphicsSceneRTree::itemsAt(const PointF &pos,
                                                      Spatials spat) const {
  std::list<GraphicsItem *> retval;
  switch (spat) {
  case Spatials::Contains:
    tree_.query(
        bg::index::contains(pos),
        boost::make_function_output_iterator([&retval](const ValueType &val) {
          retval.push_back(val.second.get());
        }));
    break;
  case Spatials::Intersects:
    tree_.query(
        bg::index::intersects(pos),
        boost::make_function_output_iterator([&retval](const ValueType &val) {
          retval.push_back(val.second.get());
        }));
    break;
  case Spatials::Within:
    break;
  }
  return retval;
}

std::list<GraphicsItem *> GraphicsSceneRTree::itemsAt(const Box &box,
                                                      Spatials   spat) const {
  std::list<GraphicsItem *> retval;
  switch (spat) {
  case Spatials::Contains:
    tree_.query(
        bg::index::contains(box),
        boost::make_function_output_iterator([&retval](const ValueType &val) {
          retval.push_back(val.second.get());
        }));
    break;
  case Spatials::Intersects:
    tree_.query(
        bg::index::intersects(box),
        boost::make_function_output_iterator([&retval](const ValueType &val) {
          retval.push_back(val.second.get());
        }));
    break;
  case Spatials::Within:
    tree_.query(
        bg::index::within(box),
        boost::make_function_output_iterator([&retval](const ValueType &val) {
          retval.push_back(val.second.get());
        }));
    break;
  }
  return retval;
}

size_t GraphicsSceneRTree::size() const {
  return tree_.size();
}

bool GraphicsSceneRTree::empty() const {
  return tree_.empty();
}

void GraphicsSceneRTree::clear() {
  tree_.clear();
}

Box GraphicsSceneRTree::bounds() const {
  return tree_.bounds();
}

void GraphicsSceneRTree::itemChanged(const GraphicsItem *item,
                                     const PointF &      prevPos) {
  if (item) {
    std::shared_ptr<GraphicsItem> copyItem;

    // first find item and save it, and remove for current tree
    for (auto i = tree_.qbegin(bg::index::intersects(prevPos));
         i != tree_.qend();
         ++i) {
      if (i->second.get() == item) {
        copyItem = i->second;
        tree_.remove(*i);
        break;
      }
    }

    // if we find it - add again in new position
    if (copyItem) {
      addItem(std::move(copyItem));
    }
  }
}
} // namespace KaliLaska
