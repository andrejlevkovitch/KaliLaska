// GraphicsScene.hpp

#pragma once

#include <memory>

namespace KaliLaska {
class GraphicsSceneImp;

class Event;

class SceneMouseMoveEvent;
class SceneMousePressEvent;
class SceneMouseReleaseEvent;

class KeyPressEvent;
class KeyReleaseEvent;

/**\brief store and manage GraphicsItem-s
 */
class GraphicsScene {
public:
  GraphicsScene();
  virtual ~GraphicsScene();

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
