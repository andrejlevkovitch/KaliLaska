// GraphicsSceneRTree.hpp

#pragma once

#include "graphics/imp/GraphicsSceneImp.hpp"
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/index/rtree.hpp>

#define MAX_NUMBER_OF_ELEMENTS 65535

namespace KaliLaska {
class GraphicsSceneRTree final : public GraphicsSceneImp {
  using PointType = boost::geometry::model::d2::point_xy<int>;
  using BoxType   = boost::geometry::model::box<PointType>;

  using Indexable = boost::geometry::index::quadratic<MAX_NUMBER_OF_ELEMENTS>;

public:
  GraphicsSceneRTree();
  ~GraphicsSceneRTree() override;

  GraphicsSceneRTree(const GraphicsSceneRTree &) = delete;
  GraphicsSceneRTree &operator=(const GraphicsSceneRTree &) = delete;

private:
  boost::geometry::index::rtree<BoxType, Indexable> tree_;
};

} // namespace KaliLaska
