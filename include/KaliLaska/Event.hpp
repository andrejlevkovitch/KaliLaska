// Event.hpp

#pragma once

#include "kalilaska_export.h"
#include <cstdint>
#include <ostream>

namespace KaliLaska {

namespace Mouse {
enum class Click { Invalid, Single, Double };
enum Button { Invalid = 0, Left = 1, Middle = 2, Right = 4 };
enum class Scale { Invalid, ScaleUp, ScaleDown };
using Buttons = uint32_t;
enum class Focus { Invalid, Enter, Leave };
} // namespace Mouse

enum class ShowAction {
  Invalid,
  Shown,
  Hidden,
  // Minimized,
  // Maximized,
  // Restored
};

/**\brief base class for all events
 */
class KALILASKA_EXPORT Event {
public:
  enum class Type {
    Invalid,
    CloseEvent,
    ShowEvent,
    ResizeEvent,
    MouseFocusEvent,
    MousePressEvent,
    MouseReleaseEvent,
    MouseMoveEvent,
    MouseWheelEvent,
  };

  Event(Type type);
  virtual ~Event() = default;

  Type type() const;

private:
  Type type_;
};

std::ostream &operator<<(std::ostream &stream, const Event &event);
} // namespace KaliLaska
