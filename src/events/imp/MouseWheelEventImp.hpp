// MouseWheelEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"

namespace KaliLaska {
class MouseWheelEventImp {
public:
  virtual ~MouseWheelEventImp() = default;

  virtual Point          position() const = 0;
  virtual Mouse::Buttons buttons() const  = 0;
  virtual Mouse::Scale   scale() const    = 0;
};
} // namespace KaliLaska
