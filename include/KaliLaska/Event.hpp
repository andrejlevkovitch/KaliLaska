// Event.hpp

#pragma once

#include "kalilaska_export.h"
#include <cstdint>
#include <ostream>

namespace KaliLaska {

namespace Mouse {
enum class Click {
  Invalid,
  Single,
  Double,
};
/**\brief bit masks
 */
enum Button : uint8_t {
  Invalid = 0,
  Left    = 1,
  Middle  = 2,
  Right   = 4,
};
using Buttons = uint8_t;

enum class Scale {
  Invalid,
  ScaleUp,
  ScaleDown,
};
enum class Focus {
  Invalid,
  Enter,
  Leave,
};
} // namespace Mouse

namespace Keyboard {
enum class Focus {
  Invalid,
  Gained,
  Lost,
};
/**\brief bit masks
 */
enum Mod : uint8_t {
  Invalid = 0,
  Shift   = 1,
  Ctrl    = 2,
  Alt     = 4,
};
enum class Key {
  Invalid,
  Key_0,
  Key_1,
  Key_2,
  Key_3,
  Key_4,
  Key_5,
  Key_6,
  Key_7,
  Key_8,
  Key_9,
  Key_A,
  Key_B,
  Key_C,
  Key_D,
  Key_E,
  Key_F,
  Key_G,
  Key_H,
  Key_I,
  Key_J,
  Key_K,
  Key_L,
  Key_M,
  Key_N,
  Key_O,
  Key_P,
  Key_Q,
  Key_R,
  Key_S,
  Key_T,
  Key_U,
  Key_V,
  Key_W,
  Key_X,
  Key_Y,
  Key_Z,
  Key_Space,
  Key_Enter,
  Key_Up,
  Key_Down,
  Key_Left,
  Key_Right,
  Key_Ctrl,
  Key_Alt,
  Key_Shift,
};
using Modifyers = uint8_t;
} // namespace Keyboard

enum class ShowAction {
  Invalid,
  Shown,
  Hidden,
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
    MoveEvent,

    MouseFocusEvent,
    MousePressEvent,
    MouseReleaseEvent,
    MouseMoveEvent,
    MouseWheelEvent,

    KeyboardFocusEvent,
    KeyPressEvent,
    KeyReleaseEvent,

    SceneMouseMoveEvent,
    SceneMousePressEvent,
    SceneMouseReleaseEvent,

    /**\brief if you want to implement you'r event type - use values after the
     * value
     */
    UserType = 100,
  };

  explicit Event(Type type);
  virtual ~Event() = default;

  Type type() const;

private:
  Type type_;
};
} // namespace KaliLaska

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &          stream,
                                          const KaliLaska::Event &event);
