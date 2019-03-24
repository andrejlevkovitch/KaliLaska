// MousePressEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class MousePressEventImp;
class EventFactory;

/**\brief generates after press on window screen
 */
class KALILASKA_EXPORT MousePressEvent : public Event {
  friend EventFactory;

public:
  MousePressEvent(Mouse::Button button, Mouse::Click click, Point pos);

  ~MousePressEvent() override;

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
  explicit MousePressEvent(std::unique_ptr<MousePressEventImp> imp);

private:
  std::unique_ptr<MousePressEventImp> imp_;
};
} // namespace KaliLaska

KALILASKA_EXPORT std::ostream &
                 operator<<(std::ostream &stream, const KaliLaska::MousePressEvent &event);
