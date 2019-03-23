// MouseWheelEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class MouseWheelEventImp;
class EventFactory;

/**\brief generates after change wheel state above window
 */
class KALILASKA_EXPORT MouseWheelEvent final : public Event {
  friend EventFactory;

public:
  explicit MouseWheelEvent(Mouse::Scale scale);

  ~MouseWheelEvent() override;

  Point        position() const;
  Mouse::Scale scale() const;

private:
  explicit MouseWheelEvent(std::unique_ptr<MouseWheelEventImp> imp);

private:
  std::unique_ptr<MouseWheelEventImp> imp_;
};

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &         stream,
                                          const MouseWheelEvent &event);
} // namespace KaliLaska
