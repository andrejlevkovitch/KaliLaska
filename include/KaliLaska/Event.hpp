// Event.hpp

#pragma once

#include <cstdint>
#include <ostream>

namespace KaliLaska {

namespace Mouse {
enum Button { Invalid = 0, Left = 1, Middle = 2, Right = 4 };
enum class Scale { Invalid, ScaleUp, ScaleDown };
using Buttons = uint32_t;
} // namespace Mouse

/**\brief base class for all events
 */
class Event {
public:
  enum class Type {
    CloseEvent,
    MousePressEvent,
    MouseReleaseEvent,
    MouseMoveEvent,
    MouseWheelEvent
  };

  Event(Type type);
  virtual ~Event() = default;

  Type type() const;

private:
  Type type_;
};

std::ostream &operator<<(std::ostream &stream, const Event &event);
} // namespace KaliLaska
