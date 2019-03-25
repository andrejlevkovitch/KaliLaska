// IteratorImp.hpp

#pragma once

#include "graphics/imp/GraphicsSceneImp.hpp"

namespace KaliLaska {
class GraphicsItem;

class IteratorImp {
public:
  IteratorImp(GraphicsSceneImp::SceneIterator iter);
  GraphicsItem *operator*() const;
  GraphicsItem *operator->() const;

  IteratorImp &operator++();
  IteratorImp &operator++(int);

private:
  GraphicsSceneImp::SceneIterator iter_;
};
} // namespace KaliLaska
