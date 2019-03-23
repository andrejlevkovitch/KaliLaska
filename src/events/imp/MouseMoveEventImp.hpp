// MouseMoveEventImp.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"

namespace KaliLaska {
class MouseMoveEventImp {
public:
  virtual ~MouseMoveEventImp() = default;

  /**\return bit mask of pressed buttons
   */
  virtual Mouse::Buttons buttons() const = 0;

  virtual Point currentPos() const  = 0;
  virtual Point previousPos() const = 0;
};
} // namespace KaliLaska
