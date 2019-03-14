// MouseFocusEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/imp/MouseFocusEventImp.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class KALILASKA_EXPORT MouseFocusEvent final : public Event {
public:
  /**\brief constructor for user events
   */
  MouseFocusEvent(Mouse::Focus focus);

  /**\warning this constructor can not be used by user!
   */
  MouseFocusEvent(std::unique_ptr<MouseFocusEventImp> imp);

  Mouse::Focus focus() const;

private:
  std::unique_ptr<MouseFocusEventImp> imp_;
};

std::ostream &operator<<(std::ostream &stream, const MouseFocusEvent &event);
} // namespace KaliLaska
