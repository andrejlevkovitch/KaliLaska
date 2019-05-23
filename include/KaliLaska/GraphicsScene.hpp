// GraphicsScene.hpp

#pragma once

#include "KaliLaska/AbstractGraphicsItem.hpp"
#include "KaliLaska/Box.hpp"
#include "KaliLaska/Object.hpp"
#include "KaliLaska/Point.hpp"
#include "KaliLaska/geometry.hpp"
#include <list>
#include <memory>

#define DEFAULT_ITEM_COMPARATOR                                                \
  [](const AbstractGraphicsItem *lhs, const AbstractGraphicsItem *rhs) {       \
    if (lhs->zvalue() < rhs->zvalue() ||                                       \
        (lhs->zvalue() == rhs->zvalue() && lhs->isAbove(rhs))) {               \
      return true;                                                             \
    }                                                                          \
    return false;                                                              \
  }

namespace KaliLaska {
class GraphicsView;

class GraphicsSceneImp;

class Event;

class SceneMouseMoveEvent;
class SceneMousePressEvent;
class SceneMouseReleaseEvent;

class KeyPressEvent;
class KeyReleaseEvent;

class MouseFocusEvent;

class SceneIterator;

class NotModificableState;
class NotifySceneState;

/**\brief store and manage AbstractGraphicsItem-s.
 * \waring all operation with inserting or removing elements invalidate
 * iterators
 */
class GraphicsScene : public Object {
  friend GraphicsView;

  friend NotifySceneState;

public:
  class ConstIterator;

  GraphicsScene();
  virtual ~GraphicsScene();

  /**\breif call update for every item on the scene
   */
  void update() override;

  AbstractGraphicsItem *itemAt(const PointF &pos,
                               std::function<bool(const AbstractGraphicsItem *,
                                                  const AbstractGraphicsItem *)>
                                   comparator = DEFAULT_ITEM_COMPARATOR,
                               Spatials       = Spatials::Intersects) const;
  std::list<AbstractGraphicsItem *>
  itemsAt(const PointF &                                    pos,
          std::function<bool(const AbstractGraphicsItem *,
                             const AbstractGraphicsItem *)> comparator =
              DEFAULT_ITEM_COMPARATOR,
          Spatials = Spatials::Intersects) const;
  std::list<AbstractGraphicsItem *>
  itemsAt(const Box &                                       pos,
          std::function<bool(const AbstractGraphicsItem *,
                             const AbstractGraphicsItem *)> comparator =
              DEFAULT_ITEM_COMPARATOR,
          Spatials = Spatials::Intersects) const;

  /**\warning after inserting all iterators invalidated
   * \return true if item added, oterwise - false
   */
  AbstractGraphicsItem *addItem(std::shared_ptr<AbstractGraphicsItem> item);
  /**\warning after removing all iterators invalidated
   * \return capacity of removing items
   */
  int removeItem(AbstractGraphicsItem *item);
  /**\warning after removing all iterators invalidated
   * \return capacity of removing items
   */
  int removeItem(const ConstIterator &iter);

  /**\warning any changes with scene or items can invalidate iterator. Be
   * carefull in use. For example: if you need change position of every item,
   * then create list of pointers to items (by copy algorithm) and change
   * position of items form the list
   *
   * \warning values not sorted by zvalue
   */
  ConstIterator begin() const;
  ConstIterator end() const;

  size_t size() const;
  bool   empty() const;

  void clear();

  /**\return minimal Box, which can contain all items
   */
  Box bounds() const;

  /**\brief AbstractGraphicsItem call this in itemChanged method. It needed for
   * change item in rtree
   *
   * \param prevPos have to position which in bounding box of item (prefer
   * centroid of boundingBox)
   *
   * \warning no reason use this manually
   */
  void itemChanged(const AbstractGraphicsItem *item, const PointF &prevPos);

  /**\breif grabb item, for ungrab set nullptr (or other item) in the method
   */
  void grabbItem(AbstractGraphicsItem *item);
  /**\return currently grabbed item or nullptr
   */
  AbstractGraphicsItem *grabbedItem() const;

  void stackAbove(AbstractGraphicsItem *item);

protected:
  /**\brief notify all items at position of event. If some item is grabbed, then
   * change postion of this to current mouse point
   */
  virtual void mouseMoveEvent(SceneMouseMoveEvent *event);
  /**\brief notify all items at position of event
   */
  virtual void mousePressEvent(SceneMousePressEvent *event);
  /**\brief notify all items at position of event
   */
  virtual void mouseReleaseEvent(SceneMouseReleaseEvent *event);

  /**\brief by default does nothing
   */
  virtual void keyPressEvent(KeyPressEvent *event);
  /**\brief by default does nothing
   */
  virtual void keyReleaseEvent(KeyReleaseEvent *event);

  /**\brief by default does nothing
   */
  virtual void mouseFocusEvent(MouseFocusEvent *event);

  /**\brief by default does nothing
   */
  virtual void event(Event *event);

private:
  std::unique_ptr<GraphicsSceneImp> imp_;

  AbstractGraphicsItem *grabbed_;

  size_t lastIndex_;

public:
  class ConstIterator final {
    friend GraphicsScene;

  public:
    ~ConstIterator();

    ConstIterator(const ConstIterator &rhs);
    ConstIterator &operator=(const ConstIterator &rhs);

    AbstractGraphicsItem *operator*() const;
    AbstractGraphicsItem *operator->() const;

    ConstIterator &operator++();
    ConstIterator &operator++(int);

    bool operator==(const ConstIterator &rhs) const;
    bool operator!=(const ConstIterator &rhs) const;

  private:
    ConstIterator(std::unique_ptr<SceneIterator> imp);

  private:
    std::unique_ptr<SceneIterator> imp_;
  };
};
} // namespace KaliLaska

namespace std {
template <>
struct iterator_traits<KaliLaska::GraphicsScene::ConstIterator> {
  using iterator_category = std::forward_iterator_tag;
  using value_type        = KaliLaska::AbstractGraphicsItem *;
  using pointer           = KaliLaska::AbstractGraphicsItem *;
  using reference         = KaliLaska::AbstractGraphicsItem *;
  using difference_type   = std::ptrdiff_t;
};
} // namespace std
