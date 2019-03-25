// SceneIteratorImp.hpp

#pragma once

#include <iterator>

namespace KaliLaska {
class GraphicsItem;
class SceneIteratorImp {
public:
  virtual ~SceneIteratorImp() = default;

  virtual GraphicsItem *operator*() const  = 0;
  virtual GraphicsItem *operator->() const = 0;

  virtual SceneIteratorImp &operator++()    = 0;
  virtual SceneIteratorImp &operator++(int) = 0;

private:
};
} // namespace KaliLaska

namespace std {
template <>
struct iterator_traits<KaliLaska::SceneIteratorImp> {
  using iterator_category = std::forward_iterator_tag;
  using value_type        = KaliLaska::GraphicsItem *;
  using pointer           = KaliLaska::GraphicsItem *;
  using reference         = KaliLaska::GraphicsItem *;
};
} // namespace std
