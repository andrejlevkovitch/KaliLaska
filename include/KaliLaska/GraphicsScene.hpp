// GraphicsScene.hpp

#pragma once

#include "KaliLaska/Box.hpp"
#include "KaliLaska/Object.hpp"
#include "KaliLaska/Point.hpp"
#include "KaliLaska/geometry.hpp"
#include <list>
#include <memory>

namespace KaliLaska {
class GraphicsView;

class GraphicsSceneImp;

class GraphicsItem;

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

/**\brief store and manage GraphicsItem-s.
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

  GraphicsItem *            itemAt(const PointF &pos,
                                   Spatials = Spatials::Intersects) const;
  std::list<GraphicsItem *> itemsAt(const PointF &pos,
                                    Spatials = Spatials::Intersects) const;
  std::list<GraphicsItem *> itemsAt(const Box &pos,
                                    Spatials = Spatials::Intersects) const;

  /**\warning after inserting all iterators invalidated
   */
  void addItem(std::shared_ptr<GraphicsItem> item);
  /**\warning after removing all iterators invalidated
   */
  void removeItem(GraphicsItem *item);
  /**\warning after removing all iterators invalidated
   */
  void removeItem(const ConstIterator &iter);

  ConstIterator begin() const;
  ConstIterator end() const;

  size_t size() const;
  bool   empty() const;

  void clear();

  /**\return minimal Box, which can contain all items
   */
  Box bounds() const;

  /**\brief GraphicsItem call this in itemChanged method. It needed for change
   * item in rtree \warning no reason use this manually
   */
  void itemChanged(const GraphicsItem *item, const PointF &prevPos);

protected:
  /**\brief notify all items at position of event
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

public:
  class ConstIterator final {
    friend GraphicsScene;

  public:
    ~ConstIterator();

    ConstIterator(const ConstIterator &rhs);
    ConstIterator &operator=(const ConstIterator &rhs);

    GraphicsItem *operator*() const;
    GraphicsItem *operator->() const;

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
  using value_type        = KaliLaska::GraphicsItem *;
  using pointer           = KaliLaska::GraphicsItem *;
  using reference         = KaliLaska::GraphicsItem *;
  using difference_type   = std::ptrdiff_t;
};
} // namespace std
