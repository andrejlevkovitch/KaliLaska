// MousePressEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"
#include "KaliLaska/imp/MousePressEventImp.hpp"
#include <memory>

namespace KaliLaska {
class MousePressEventImp;

class MousePressEvent final : public Event {
public:
  MousePressEvent(Mouse::Button button, Point pos);

  MousePressEvent(std::unique_ptr<MousePressEventImp> imp);

  /**\return pressed button (only one)
   */
  Mouse::Button button() const;

  /**\return all pressed buttons
   */
  Mouse::Buttons buttons() const;

  /**\return click position in window coordinates
   */
  Point clickPos() const;

private:
  std::unique_ptr<MousePressEventImp> imp_;
};

std::ostream &operator<<(std::ostream &stream, const MousePressEvent &event);
} // namespace KaliLaska
