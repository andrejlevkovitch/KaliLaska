// MousePressEventImp.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"

namespace KaliLaska {
class MousePressEventImp {
public:
  virtual ~MousePressEventImp() = default;

  virtual Mouse::Button  button() const   = 0;
  virtual Mouse::Buttons buttons() const  = 0;
  virtual Mouse::Click   click() const    = 0;
  virtual Point          clickPos() const = 0;
};
} // namespace KaliLaska
