// EventImpFactory.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class CloseEventImp;
class ShowEventImp;
class ResizeEventImp;
class MouseFocusEventImp;
class MousePressEventImp;
class MouseReleaseEventImp;
class MouseMoveEventImp;
class MouseWheelEventImp;

class Point;
class Size;

/**\brief this factory create event implementations from user data. This class
 * need because we can not create abstract base class, and we can not set
 * certain implementation. So we need abstract factory, which will be create
 * this
 */
class KALILASKA_EXPORT EventImpFactory {
public:
  virtual ~EventImpFactory() = default;

  virtual std::unique_ptr<CloseEventImp> createCloseEventImp() = 0;

  virtual std::unique_ptr<ShowEventImp>
  createShowEventImp(ShowAction action) = 0;

  virtual std::unique_ptr<ResizeEventImp> createResizeEventImp(Size prev,
                                                               Size next) = 0;

  virtual std::unique_ptr<MousePressEventImp> createMousePressImp(
      Mouse::Button button, Mouse::Click click, Point clickPos) = 0;

  virtual std::unique_ptr<MouseReleaseEventImp>
  createMouseReleaseImp(Mouse::Button button, Point clickPos) = 0;

  virtual std::unique_ptr<MouseMoveEventImp> createMouseMoveEventImp(
      Mouse::Buttons buttons, Point curPos, Point prevPos) = 0;

  virtual std::unique_ptr<MouseWheelEventImp>
  createMouseWheelEventImp(Mouse::Scale scale) = 0;

  virtual std::unique_ptr<MouseFocusEventImp>
  createMouseFocusEvent(Mouse::Focus focus) = 0;
};
} // namespace KaliLaska
