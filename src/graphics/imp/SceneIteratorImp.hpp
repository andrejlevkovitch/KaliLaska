// SceneIteratorImp.hpp

#pragma once

#include <iterator>
#include <memory>

namespace KaliLaska {
class GraphicsItem;
class SceneIteratorImp {
public:
  virtual ~SceneIteratorImp() = default;

  virtual GraphicsItem *operator*() const  = 0;
  virtual GraphicsItem *operator->() const = 0;

  virtual SceneIteratorImp &operator++()    = 0;
  virtual SceneIteratorImp &operator++(int) = 0;

  virtual bool operator==(const SceneIteratorImp &rhs) const = 0;
  virtual bool operator!=(const SceneIteratorImp &rhs) const = 0;

  /**\brief this method needed for copy SceneIterator, which contains unique_ptr
   * with object of this class
   */
  virtual std::unique_ptr<SceneIteratorImp> copyItSelf() const = 0;
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
