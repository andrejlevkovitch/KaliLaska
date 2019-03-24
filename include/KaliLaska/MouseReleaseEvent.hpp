// MouseReleaseEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class MouseReleaseEventImp;
class EventFactory;

/**\brief generates after release mouse button above screen
 */
class KALILASKA_EXPORT MouseReleaseEvent : public Event {
  friend EventFactory;

public:
  MouseReleaseEvent(Mouse::Button button, Point clickPos);

  ~MouseReleaseEvent() override;

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
  explicit MouseReleaseEvent(std::unique_ptr<MouseReleaseEventImp> imp);

private:
  std::unique_ptr<MouseReleaseEventImp> imp_;
};
} // namespace KaliLaska

KALILASKA_EXPORT std::ostream &
                 operator<<(std::ostream &stream, const KaliLaska::MouseReleaseEvent &event);
