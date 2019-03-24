// GraphicsItem.hpp

#pragma once

#include <memory>

namespace KaliLaska {
class Event;

class SceneMouseMoveEvent;
class SceneMousePressEvent;
class SceneMouseReleaseEvent;

/**\brief represent graphical objects on scene
 */
class GraphicsItem {
public:
  GraphicsItem();
  virtual ~GraphicsItem() = default;

protected:
  virtual void mouseMoveEvent(std::unique_ptr<SceneMouseMoveEvent> event);
  virtual void mousePressEvent(std::unique_ptr<SceneMousePressEvent> event);
  virtual void mouseReleaseEvent(std::unique_ptr<SceneMouseReleaseEvent> event);

  virtual void userEvent(std::unique_ptr<Event> event);

private:
};
} // namespace KaliLaska
