// GraphicsSceneRTree.hpp

#pragma once

#include "graphics/imp/GraphicsSceneImp.hpp"
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/index/rtree.hpp>

#define MAX_NUMBER_OF_ELEMENTS_IN_NODE 16

namespace KaliLaska {
class GraphicsSceneRTree final : public GraphicsSceneImp {
public:
  using BoxType   = boost::geometry::model::box<Point>;
  using ValueType = std::pair<BoxType, GraphicsItem *>;
  using Indexable =
      boost::geometry::index::quadratic<MAX_NUMBER_OF_ELEMENTS_IN_NODE>;
  using TreeType = boost::geometry::index::rtree<ValueType, Indexable>;

  GraphicsItem *            itemAt(const Point &pos) const override;
  std::list<GraphicsItem *> itemsAt(const Point &pos) const override;

  SceneIterator begin() const override;
  SceneIterator end() const override;

  GraphicsSceneRTree();
  ~GraphicsSceneRTree() override;

  GraphicsSceneRTree(const GraphicsSceneRTree &) = delete;
  GraphicsSceneRTree &operator=(const GraphicsSceneRTree &) = delete;

private:
  TreeType tree_;
};

} // namespace KaliLaska
