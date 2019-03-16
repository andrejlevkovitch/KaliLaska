// MouseMoveEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"
#include "KaliLaska/imp/MouseMoveEventImp.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class KALILASKA_EXPORT MouseMoveEvent final : public Event {
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

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &        stream,
                                          const MouseMoveEvent &event);
} // namespace KaliLaska
