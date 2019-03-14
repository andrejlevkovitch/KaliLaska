// MouseWheelEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"
#include "KaliLaska/imp/MouseWheelEventImp.hpp"
#include "KaliLaska/kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class KALILASKA_EXPORT MouseWheelEvent final : public Event {
public:
  MouseWheelEvent(Mouse::Scale scale);

  MouseWheelEvent(std::unique_ptr<MouseWheelEventImp> imp);

  Point        position() const;
  Mouse::Scale scale() const;

private:
  std::unique_ptr<MouseWheelEventImp> imp_;
};

std::ostream &operator<<(std::ostream &stream, const MouseWheelEvent &event);
} // namespace KaliLaska
