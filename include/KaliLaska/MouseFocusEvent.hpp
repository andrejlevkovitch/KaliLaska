// MouseFocusEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class MouseFocusEventImp;
class EventFactory;

class KALILASKA_EXPORT MouseFocusEvent final : public Event {
  friend EventFactory;

public:
  /**\brief constructor for user events
   */
  explicit MouseFocusEvent(Mouse::Focus focus);

  ~MouseFocusEvent() override;

  Mouse::Focus focus() const;

private:
  explicit MouseFocusEvent(std::unique_ptr<MouseFocusEventImp> imp);

private:
  std::unique_ptr<MouseFocusEventImp> imp_;
};

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &         stream,
                                          const MouseFocusEvent &event);
} // namespace KaliLaska
