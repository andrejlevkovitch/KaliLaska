// SceneIteratorRTree.hpp

#pragma once

#include "GraphicsSceneRTree.hpp"
#include "graphics/imp/SceneIteratorImp.hpp"

namespace KaliLaska {
class SceneIteratorRTree final : public SceneIteratorImp {
public:
  SceneIteratorRTree(const GraphicsSceneRTree::TreeType::const_iterator &it);
  ~SceneIteratorRTree() override;

  GraphicsItem *operator*() const override;
  GraphicsItem *operator->() const override;

  SceneIteratorRTree &operator++() override;
  SceneIteratorRTree &operator++(int) override;

private:
  GraphicsSceneRTree::TreeType::const_iterator it_;
};
} // namespace KaliLaska
