// KeyboardFocusEvent.hpp

#pragma once
#include "KaliLaska/Event.hpp"
#include "KaliLaska/imp/KeyboardFocusEventImp.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class KALILASKA_EXPORT KeyboardFocusEvent final : public Event {
public:
  /**\brief konstructor for user events
   */
  explicit KeyboardFocusEvent(Keyboard::Focus focus);

  explicit KeyboardFocusEvent(std::unique_ptr<KeyboardFocusEventImp> imp);

  /**\brief current changed of keyboard focus
   */
  Keyboard::Focus focus() const;

private:
  std::unique_ptr<KeyboardFocusEventImp> imp_;
};

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &            stream,
                                          const KeyboardFocusEvent &event);
} // namespace KaliLaska
