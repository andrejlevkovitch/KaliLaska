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

class IteratorImp;

/**\brief store and manage GraphicsItem-s
 */
class GraphicsScene {
public:
  GraphicsScene();
  virtual ~GraphicsScene();

  GraphicsItem *            itemAt(const Point &pos) const;
  std::list<GraphicsItem *> itemsAt(const Point &pos) const;

public:
  class ConstIterator {
    friend GraphicsScene;

  public:
    ConstIterator() = default;
    ~ConstIterator();

    GraphicsItem *operator*() const;
    GraphicsItem *operator->() const;

    ConstIterator &operator++();
    ConstIterator &operator++(int);

  private:
    ConstIterator(std::unique_ptr<IteratorImp> imp);

  private:
    std::unique_ptr<IteratorImp> imp_;
  };

  ConstIterator begin() const;
  ConstIterator end() const;

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
};
} // namespace std
