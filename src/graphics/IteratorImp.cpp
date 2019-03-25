// IteratorImp.cpp

#include "IteratorImp.hpp"

namespace KaliLaska {
IteratorImp::IteratorImp(GraphicsSceneImp::SceneIterator iter)
    : iter_{std::move(iter)} {
}

GraphicsItem *IteratorImp::operator*() const {
  return iter_.operator*();
}

GraphicsItem *IteratorImp::operator->() const {
  return iter_.operator->();
}

IteratorImp &IteratorImp::operator++() {
  ++iter_;
  return *this;
}

IteratorImp &IteratorImp::operator++(int) {
  ++iter_;
  return *this;
}
} // namespace KaliLaska
