// KeyboardFocusEvent.hpp

#pragma once
#include "KaliLaska/Event.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class KeyboardFocusEventImp;
class EventFactory;

/**\brief generates when window get or loses focus of keyboard
 */
class KALILASKA_EXPORT KeyboardFocusEvent : public Event {
  friend EventFactory;

public:
  /**\brief konstructor for user events
   */
  explicit KeyboardFocusEvent(Keyboard::Focus focus);

  ~KeyboardFocusEvent() override;

  /**\brief current changed of keyboard focus
   */
  Keyboard::Focus focus() const;

private:
  explicit KeyboardFocusEvent(std::unique_ptr<KeyboardFocusEventImp> imp);

private:
  std::unique_ptr<KeyboardFocusEventImp> imp_;
};
} // namespace KaliLaska

KALILASKA_EXPORT std::ostream &
                 operator<<(std::ostream &stream, const KaliLaska::KeyboardFocusEvent &event);
