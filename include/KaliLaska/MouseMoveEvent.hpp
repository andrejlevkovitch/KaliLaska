// MouseMoveEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class MouseMoveEventImp;
class EventFactory;

/**\brief generates after move mouse above window
 */
class KALILASKA_EXPORT MouseMoveEvent : public Event {
  friend EventFactory;

public:
  MouseMoveEvent(Mouse::Buttons buttons, Point currentPos, Point previousPos);

  ~MouseMoveEvent() override;

  Mouse::Buttons buttons() const;
  Point          currentPos() const;
  Point          previousPos() const;
  Point          distance() const;

private:
  explicit MouseMoveEvent(std::unique_ptr<MouseMoveEventImp> imp);

private:
  std::unique_ptr<MouseMoveEventImp> imp_;
};
} // namespace KaliLaska

KALILASKA_EXPORT std::ostream &
                 operator<<(std::ostream &stream, const KaliLaska::MouseMoveEvent &event);
