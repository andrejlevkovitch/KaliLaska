// MouseReleaseEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"
#include <memory>

namespace KaliLaska {
class MouseReleaseEventImp;

class MouseReleaseEvent final : public Event {
public:
  MouseReleaseEvent(Mouse::Button button, Point clickPos);

  MouseReleaseEvent(std::unique_ptr<MouseReleaseEventImp> imp);

  /**\return released button (only one)
   */
  Mouse::Button button() const;

  /**\return all pressed buttons
   */
  Mouse::Buttons buttons() const;

  /**\return click position in window coordinates
   */
  Point clickPos() const;

private:
  std::unique_ptr<MouseReleaseEventImp> imp_;
};

std::ostream &operator<<(std::ostream &stream, const MouseReleaseEvent &event);
} // namespace KaliLaska