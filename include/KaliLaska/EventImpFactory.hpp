// EventImpFactory.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include <memory>

namespace KaliLaska {
class CloseEventImp;
class MousePressEventImp;
class MouseReleaseEventImp;
class MouseMoveEventImp;
class MouseWheelEventImp;

class Point;

/**\brief this factory create event implementations from user data
 */
class EventImpFactory {
public:
  virtual ~EventImpFactory() = default;

  virtual std::unique_ptr<CloseEventImp> createCloseEventImp() = 0;
  virtual std::unique_ptr<MousePressEventImp>
  createMousePressImp(Mouse::Button button, Point clickPos) = 0;
  virtual std::unique_ptr<MouseReleaseEventImp>
                                             createMouseReleaseImp(Mouse::Button button, Point clickPos) = 0;
  virtual std::unique_ptr<MouseMoveEventImp> createMouseMoveEventImp(
      Mouse::Buttons buttons, Point curPos, Point prevPos) = 0;
  virtual std::unique_ptr<MouseWheelEventImp>
  createMouseWheelEventImp(Mouse::Scale scale) = 0;
};
} // namespace KaliLaska