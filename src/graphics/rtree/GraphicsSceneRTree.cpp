// GraphicsSceneRTree.hpp

#include "GraphicsSceneRTree.hpp"
#include "KaliLaska/AbstractGraphicsItem.hpp"
#include "SceneIteratorRTree.hpp"
#include "debug.hpp"
#include "logger/logger.hpp"
#include <boost/geometry.hpp>
#include <boost/iterator/function_output_iterator.hpp>
#include <boost/qvm/mat_operations.hpp>

namespace bg = boost::geometry;
namespace bq = boost::qvm;

namespace KaliLaska {
GraphicsSceneRTree::GraphicsSceneRTree() {
  bg::index::rtree<ValueType, Indexable>::const_iterator it;
}

GraphicsSceneRTree::~GraphicsSceneRTree() {
}

AbstractGraphicsItem *
GraphicsSceneRTree::addItem(std::shared_ptr<AbstractGraphicsItem> item) {
  if (item) {
    // we can not just rotade box, so we have to get ring from this and rotade
    // it. After we get box from rotated ring and insert it in rtree
    Ring curShape;
    bg::convert(item->boundingBox(), curShape);
    if (bg::is_valid(curShape)) {
      bg::strategy::transform::matrix_transformer<float, 2, 2> traslator{
          item->matrix()};
      Ring rezRing;
      bg::transform(curShape, rezRing, traslator);
      auto retval = item.get();
      tree_.insert(
          ValueType{bg::return_envelope<Box>(rezRing), std::move(item)});
      return retval;
    }
  }
  return nullptr;
}

bool GraphicsSceneRTree::removeItem(AbstractGraphicsItem *item) {
  if (auto found = std::find(this->begin(), this->end(), item);
      found != this->end()) {
    return removeItem(found);
  }
  return 0;
}

SceneIterator GraphicsSceneRTree::begin() const {
  return SceneIterator{std::make_unique<SceneIteratorRTree>(tree_.begin())};
}

SceneIterator GraphicsSceneRTree::end() const {
  return SceneIterator{std::make_unique<SceneIteratorRTree>(tree_.end())};
}

bool GraphicsSceneRTree::removeItem(const SceneIterator &iter) {
  auto removeIter = reinterpret_cast<SceneIteratorRTree *>(iter.imp());
  auto rtreeIter  = removeIter->imp();
  // FIXME for some reason I can not use here tree_.remove(first, last) - it
  // generates error sometimes
  return tree_.remove(*rtreeIter);
}

AbstractGraphicsItem *GraphicsSceneRTree::itemAt(const PointF &pos,
                                                 Spatials      spat) const {
  static auto predicate = [&pos](const auto &val) {
    bg::strategy::transform::matrix_transformer<float, 2, 2> transform{
        bq::inverse(val.second->matrix())};
    PointF rezPos;
    bg::transform(pos, rezPos, transform);
    if (bg::intersects(rezPos, val.second->boundingBox())) {
      return true;
    }
    return false;
  };
  switch (spat) {
  case Spatials::Contains:
    for (auto iter = tree_.qbegin(bg::index::contains(pos));
         iter != tree_.qend();
         ++iter) {
      if (predicate(*iter)) {
        return iter->second.get();
      }
    }
    break;
  case Spatials::Intersects:
    for (auto iter = tree_.qbegin(bg::index::intersects(pos));
         iter != tree_.qend();
         ++iter) {
      if (predicate(*iter)) {
        return iter->second.get();
      }
    }
    break;
  case Spatials::Within:
    break;
  }
  return nullptr;
}

std::list<AbstractGraphicsItem *>
GraphicsSceneRTree::itemsAt(const PointF &pos, Spatials spat) const {
  std::list<AbstractGraphicsItem *> retval;
  switch (spat) {
  case Spatials::Contains:
    tree_.query(
        bg::index::contains(pos),
        boost::make_function_output_iterator([&retval,
                                              pos](const ValueType &val) {
          bg::strategy::transform::matrix_transformer<float, 2, 2> transform{
              bq::inverse(val.second->matrix())};
          PointF rezPos;
          bg::transform(pos, rezPos, transform);
          if (bg::intersects(rezPos, val.second->boundingBox())) {
            retval.push_back(val.second.get());
          }
        }));
    break;
  case Spatials::Intersects:
    tree_.query(
        bg::index::intersects(pos),
        boost::make_function_output_iterator([&retval,
                                              pos](const ValueType &val) {
          bg::strategy::transform::matrix_transformer<float, 2, 2> transform{
              bq::inverse(val.second->matrix())};
          PointF rezPos;
          bg::transform(pos, rezPos, transform);
          if (bg::intersects(rezPos, val.second->boundingBox())) {
            retval.push_back(val.second.get());
          }
        }));
    break;
  case Spatials::Within:
    break;
  }
  return retval;
}

std::list<AbstractGraphicsItem *>
GraphicsSceneRTree::itemsAt(const Box &box, Spatials spat) const {
  std::list<AbstractGraphicsItem *> retval;
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
} // namespace KaliLaska

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

void GraphicsSceneRTree::itemChanged(const AbstractGraphicsItem *item,
                                     const PointF &              prevPos) {
  if (item) {
    std::shared_ptr<AbstractGraphicsItem> copyItem;

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

    // if we not find by point we try find by check all items
    if (!copyItem) {
      LOG_WARNING << "we not get item in rtree from previous position, so we "
                     "search it in all rtree";
      for (const auto &i : tree_) {
        if (i.second.get() == item) {
          copyItem = i.second;
          tree_.remove(i);
          break;
        }
      }
    }

    addItem(std::move(copyItem));
  }
}
} // namespace KaliLaska
