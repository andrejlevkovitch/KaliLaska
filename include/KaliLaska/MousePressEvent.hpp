// MousePressEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"
#include "KaliLaska/imp/MousePressEventImp.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class MousePressEventImp;

class KALILASKA_EXPORT MousePressEvent final : public Event {
public:
  MousePressEvent(Mouse::Button button, Mouse::Click click, Point pos);

  MousePressEvent(std::unique_ptr<MousePressEventImp> imp);

  /**\return pressed button (currently)
   */
  Mouse::Button button() const;

  /**\return all pressed buttons
   */
  Mouse::Buttons buttons() const;

  /**\return One if was only one click, and Double if was double-click
   */
  Mouse::Click click() const;

  /**\return click position in window coordinates
   */
  Point clickPos() const;

private:
  std::unique_ptr<MousePressEventImp> imp_;
};

std::ostream &operator<<(std::ostream &stream, const MousePressEvent &event);
} // namespace KaliLaska
