// MouseMoveEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"
#include <memory>

namespace KaliLaska {
class MouseMoveEventImp;

class MouseMoveEvent final : public Event {
public:
  MouseMoveEvent(Mouse::Buttons buttons, Point currentPos, Point previousPos);

  MouseMoveEvent(std::unique_ptr<MouseMoveEventImp> imp);
  ~MouseMoveEvent() override = default;

  Mouse::Buttons buttons() const;
  Point          currentPos() const;
  Point          previousPos() const;

private:
  std::unique_ptr<MouseMoveEventImp> imp_;
};

std::ostream &operator<<(std::ostream &stream, const MouseMoveEvent &event);
} // namespace KaliLaska