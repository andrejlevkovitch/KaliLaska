// GraphicsScene.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include <list>
#include <memory>

namespace KaliLaska {
class GraphicsSceneImp;

class GraphicsItem;

class Event;

class SceneMouseMoveEvent;
class SceneMousePressEvent;
class SceneMouseReleaseEvent;

class KeyPressEvent;
class KeyReleaseEvent;

class SceneIterator;

/**\brief store and manage GraphicsItem-s.
 * \waring all operation with inserting or removing elements invalidate
 * iterators
 */
class GraphicsScene {
public:
  GraphicsScene();
  virtual ~GraphicsScene();

  GraphicsItem *            itemAt(const Point &pos) const;
  std::list<GraphicsItem *> itemsAt(const Point &pos) const;

  /**\warning after inserting all iterators invalidated
   */
  void addItem(std::shared_ptr<GraphicsItem> item);
  /**\warning after removing all iterators invalidated
   */
  void removeItem(GraphicsItem *item);

public:
  class ConstIterator final {
    friend GraphicsScene;

  public:
    ConstIterator() = default;
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

  ConstIterator begin() const;
  ConstIterator end() const;

  /**\warning after removing all iterators invalidated
   */
  void removeItem(const ConstIterator &iter);

protected:
  virtual void mouseMoveEvent(std::unique_ptr<SceneMouseMoveEvent> event);
  virtual void mousePressEvent(std::unique_ptr<SceneMousePressEvent> event);
  virtual void mouseReleaseEvent(std::unique_ptr<SceneMouseReleaseEvent> event);

  virtual void keyPressEvent(std::unique_ptr<KeyPressEvent> event);
  virtual void keyReleaseEvent(std::unique_ptr<KeyReleaseEvent> event);

  virtual void event(std::unique_ptr<Event> event);

private:
  std::unique_ptr<GraphicsSceneImp> imp_;
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
