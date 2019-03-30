// GraphicsSceneImp.hpp

#pragma once

#include "KaliLaska/Box.hpp"
#include "KaliLaska/Point.hpp"
#include "KaliLaska/geometry.hpp"
#include <iterator>
#include <list>
#include <memory>

namespace KaliLaska {
class GraphicsItem;

class SceneIteratorImp;

/**\warning be careful while copy this iterator. Here using std::unique_ptr
 * for implementation of iterator, so in inheritances classes have to be
 * method, which copy itself
 */
class SceneIterator final
    : public std::iterator<std::forward_iterator_tag, GraphicsItem *> {
public:
  explicit SceneIterator(std::unique_ptr<SceneIteratorImp> imp);
  ~SceneIterator();

  GraphicsItem *operator*() const;
  GraphicsItem *operator->() const;

  SceneIterator &operator++();
  SceneIterator &operator++(int);

  SceneIterator(const SceneIterator &rhs);
  SceneIterator &operator=(const SceneIterator &rhs);

  bool operator==(const SceneIterator &rhs);
  bool operator!=(const SceneIterator &rhs);

  std::unique_ptr<SceneIterator> copyItSelf() const;

  SceneIteratorImp *imp() const;

private:
  std::unique_ptr<SceneIteratorImp> imp_;
};

/**\brief implementation of GraphicsScene
 */
class GraphicsSceneImp {
public:
  virtual ~GraphicsSceneImp() = default;

  virtual GraphicsItem *itemAt(const PointF &pos, Spatials spat) const = 0;
  virtual std::list<GraphicsItem *> itemsAt(const PointF &pos,
                                            Spatials      spat) const       = 0;
  virtual std::list<GraphicsItem *> itemsAt(const Box &box,
                                            Spatials   spat) const       = 0;

  virtual void addItem(std::shared_ptr<GraphicsItem> item) = 0;
  virtual void removeItem(GraphicsItem *item)              = 0;

  virtual size_t size() const  = 0;
  virtual bool   empty() const = 0;

  virtual void clear() = 0;

  virtual Box bounds() const = 0;

public:
  virtual SceneIterator begin() const                         = 0;
  virtual SceneIterator end() const                           = 0;
  virtual void          removeItem(const SceneIterator &iter) = 0;
};
} // namespace KaliLaska

namespace std {
template <>
struct iterator_traits<KaliLaska::SceneIterator> {
  using iterator_category = std::forward_iterator_tag;
  using value_type        = KaliLaska::GraphicsItem *;
  using pointer           = KaliLaska::GraphicsItem *;
  using reference         = KaliLaska::GraphicsItem *;
  using difference_type   = std::ptrdiff_t;
};
} // namespace std
