// EventFactory.hpp

#include <memory>

namespace KaliLaska {
class CloseEvent;
class ShowEvent;
class ResizeEvent;
class MoveEvent;
class MouseFocusEvent;
class MouseMoveEvent;
class MousePressEvent;
class MouseReleaseEvent;
class MouseWheelEvent;
class KeyboardFocusEvent;
class KeyPressEvent;
class KeyReleaseEvent;

class CloseEventImp;
class ShowEventImp;
class ResizeEventImp;
class MoveEventImp;
class MouseFocusEventImp;
class MouseMoveEventImp;
class MousePressEventImp;
class MouseReleaseEventImp;
class MouseWheelEventImp;
class KeyboardFocusEventImp;
class KeyPressEventImp;
class KeyReleaseEventImp;

/**\brief this factory incapsulate creation Event-s from its implementation (by
 * calling private konstructor). It is friend of every event
 */
class EventFactory {
public:
  static std::unique_ptr<CloseEvent> event(std::unique_ptr<CloseEventImp> imp);

  static std::unique_ptr<ShowEvent> event(std::unique_ptr<ShowEventImp> imp);

  static std::unique_ptr<ResizeEvent>
  event(std::unique_ptr<ResizeEventImp> imp);

  static std::unique_ptr<MoveEvent> event(std::unique_ptr<MoveEventImp> imp);

  static std::unique_ptr<MouseFocusEvent>
  event(std::unique_ptr<MouseFocusEventImp> imp);

  static std::unique_ptr<MouseMoveEvent>
  event(std::unique_ptr<MouseMoveEventImp> imp);

  static std::unique_ptr<MousePressEvent>
  event(std::unique_ptr<MousePressEventImp> imp);

  static std::unique_ptr<MouseReleaseEvent>
  event(std::unique_ptr<MouseReleaseEventImp> imp);

  static std::unique_ptr<MouseWheelEvent>
  event(std::unique_ptr<MouseWheelEventImp> imp);

  static std::unique_ptr<KeyboardFocusEvent>
  event(std::unique_ptr<KeyboardFocusEventImp> imp);

  static std::unique_ptr<KeyPressEvent>
  event(std::unique_ptr<KeyPressEventImp> imp);

  static std::unique_ptr<KeyReleaseEvent>
  event(std::unique_ptr<KeyReleaseEventImp> imp);
};
} // namespace KaliLaska
