// GraphicsSceneImp.hpp

#pragma once

#include <memory>

namespace KaliLaska {
class Event;

class SceneMouseMoveEvent;
class SceneMousePressEvent;
class SceneMouseReleaseEvent;

class KeyPressEvent;
class KeyReleaseEvent;

/**\brief implementation of GraphicsScene
 */
class GraphicsSceneImp {
public:
  virtual ~GraphicsSceneImp() = default;
};
} // namespace KaliLaska
