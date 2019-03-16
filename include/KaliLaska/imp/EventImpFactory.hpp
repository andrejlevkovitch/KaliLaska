// EventImpFactory.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class CloseEventImp;
class ShowEventImp;
class ResizeEventImp;
class MoveEventImp;

class MouseFocusEventImp;
class MousePressEventImp;
class MouseReleaseEventImp;
class MouseMoveEventImp;
class MouseWheelEventImp;

class KeyboardFocusEventImp;
class KeyPressEventImp;
class KeyReleaseEventImp;

class Point;
class Size;

/**\brief this factory create event implementations from user data. This class
 * needed because we can not create abstract base class, and we can not set
 * certain implementation (because it hide from us). So we need abstract
 * factory, which will be create this. Access to factory provide Application
 */
class KALILASKA_EXPORT EventImpFactory {
public:
  virtual ~EventImpFactory() = default;

  virtual std::unique_ptr<CloseEventImp> createCloseEventImp() const = 0;

  virtual std::unique_ptr<ShowEventImp>
  createShowEventImp(ShowAction action) const = 0;

  virtual std::unique_ptr<ResizeEventImp>
  createResizeEventImp(Size next) const = 0;

  virtual std::unique_ptr<MoveEventImp> createMoveEventImp(Point cur) const = 0;

  //----------------------------------------------------------------------------

  virtual std::unique_ptr<MousePressEventImp> createMousePressImp(
      Mouse::Button button, Mouse::Click click, Point clickPos) const = 0;

  virtual std::unique_ptr<MouseReleaseEventImp>
  createMouseReleaseImp(Mouse::Button button, Point clickPos) const = 0;

  virtual std::unique_ptr<MouseMoveEventImp> createMouseMoveEventImp(
      Mouse::Buttons buttons, Point curPos, Point prevPos) const = 0;

  virtual std::unique_ptr<MouseWheelEventImp>
  createMouseWheelEventImp(Mouse::Scale scale) const = 0;

  virtual std::unique_ptr<MouseFocusEventImp>
  createMouseFocusEventImp(Mouse::Focus focus) const = 0;

  //----------------------------------------------------------------------------

  virtual std::unique_ptr<KeyboardFocusEventImp>
  createKeyboardFocusEventImp(Keyboard::Focus focus) const = 0;

  virtual std::unique_ptr<KeyPressEventImp>
  createKeyPressEventImp(Keyboard::Key       key,
                         Keyboard::Modifyers modifyers,
                         bool                isRepeat) const = 0;

  virtual std::unique_ptr<KeyReleaseEventImp>
  createKeyReleaseEventImp(Keyboard::Key       key,
                           Keyboard::Modifyers modifyers) const = 0;
};
} // namespace KaliLaska
