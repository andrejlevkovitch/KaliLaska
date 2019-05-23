// GraphicsSceneImp.hpp

#pragma once

#include "KaliLaska/Box.hpp"
#include "KaliLaska/Point.hpp"
#include "KaliLaska/geometry.hpp"
#include <iterator>
#include <list>
#include <memory>

namespace KaliLaska {
class AbstractGraphicsItem;

class SceneIteratorImp;

/**\warning be careful while copy this iterator. Here using std::unique_ptr
 * for implementation of iterator, so in inheritances classes have to be
 * method, which copy itself
 */
class SceneIterator final
    : public std::iterator<std::forward_iterator_tag, AbstractGraphicsItem *> {
public:
  explicit SceneIterator(std::unique_ptr<SceneIteratorImp> imp);
  ~SceneIterator();

  AbstractGraphicsItem *operator*() const;
  AbstractGraphicsItem *operator->() const;

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

  /**\warning not consider zvalue
   */
  virtual AbstractGraphicsItem *itemAt(const PointF &pos,
                                       Spatials      spat) const = 0;
  /**\warning not consider zvalue
   */
  virtual std::list<AbstractGraphicsItem *> itemsAt(const PointF &pos,
                                                    Spatials spat) const = 0;
  /**\warning not consider zvalue
   */
  virtual std::list<AbstractGraphicsItem *> itemsAt(const Box &box,
                                                    Spatials   spat) const = 0;

  virtual AbstractGraphicsItem *
               addItem(std::shared_ptr<AbstractGraphicsItem> item) = 0;
  virtual bool removeItem(AbstractGraphicsItem *item)              = 0;

  virtual size_t size() const  = 0;
  virtual bool   empty() const = 0;

  virtual void clear() = 0;

  virtual Box bounds() const = 0;

  virtual void itemChanged(const AbstractGraphicsItem *item,
                           const PointF &              prevPos) = 0;

public:
  virtual SceneIterator begin() const                         = 0;
  virtual SceneIterator end() const                           = 0;
  virtual bool          removeItem(const SceneIterator &iter) = 0;
};
} // namespace KaliLaska

namespace std {
template <>
struct iterator_traits<KaliLaska::SceneIterator> {
  using iterator_category = std::forward_iterator_tag;
  using value_type        = KaliLaska::AbstractGraphicsItem *;
  using pointer           = KaliLaska::AbstractGraphicsItem *;
  using reference         = KaliLaska::AbstractGraphicsItem *;
  using difference_type   = std::ptrdiff_t;
};
} // namespace std
