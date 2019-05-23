// SceneIteratorRTree.hpp

#pragma once

#include "GraphicsSceneRTree.hpp"
#include "graphics/imp/SceneIteratorImp.hpp"

namespace KaliLaska {
class SceneIteratorRTree final : public SceneIteratorImp {
public:
  SceneIteratorRTree(const GraphicsSceneRTree::TreeType::const_iterator &it);
  ~SceneIteratorRTree() override;

  AbstractGraphicsItem *operator*() const override;
  AbstractGraphicsItem *operator->() const override;

  SceneIteratorRTree &operator++() override;
  SceneIteratorRTree &operator++(int) override;

  bool operator==(const SceneIteratorImp &rhs) const override;
  bool operator!=(const SceneIteratorImp &rhs) const override;

  GraphicsSceneRTree::TreeType::const_iterator imp() const;

  virtual std::unique_ptr<SceneIteratorImp> copyItSelf() const override;

private:
  GraphicsSceneRTree::TreeType::const_iterator it_;
};
} // namespace KaliLaska
