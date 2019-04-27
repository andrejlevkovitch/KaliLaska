// GraphicsSceneRTree.hpp

#pragma once

#include "KaliLaska/Box.hpp"
#include "graphics/imp/GraphicsSceneImp.hpp"
#include <boost/geometry/index/rtree.hpp>

#define MAX_NUMBER_OF_ELEMENTS_IN_NODE 16

namespace KaliLaska {
class GraphicsSceneRTree final : public GraphicsSceneImp {
public:
  using ValueType = std::pair<Box, std::shared_ptr<GraphicsItem>>;
  using Indexable =
      boost::geometry::index::quadratic<MAX_NUMBER_OF_ELEMENTS_IN_NODE>;
  using TreeType = boost::geometry::index::rtree<ValueType, Indexable>;

public:
  GraphicsSceneRTree();
  ~GraphicsSceneRTree() override;

  GraphicsSceneRTree(const GraphicsSceneRTree &) = delete;
  GraphicsSceneRTree &operator=(const GraphicsSceneRTree &) = delete;

  GraphicsItem *itemAt(const PointF &pos, Spatials spat) const override;
  std::list<GraphicsItem *> itemsAt(const PointF &pos,
                                    Spatials      spat) const override;
  std::list<GraphicsItem *> itemsAt(const Box &box,
                                    Spatials   spat) const override;

  GraphicsItem *addItem(std::shared_ptr<GraphicsItem> item) override;
  bool          removeItem(GraphicsItem *item) override;
  bool          removeItem(const SceneIterator &iter) override;

  SceneIterator begin() const override;
  SceneIterator end() const override;

  size_t size() const override;
  bool   empty() const override;

  void clear() override;

  Box bounds() const override;

  void itemChanged(const GraphicsItem *item, const PointF &prevPos) override;

private:
  TreeType tree_;
};
} // namespace KaliLaska
