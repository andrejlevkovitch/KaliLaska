// MouseMoveEventImp.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"
#include "kalilaska_export.h"

namespace KaliLaska {
class KALILASKA_EXPORT MouseMoveEventImp {
public:
  virtual ~MouseMoveEventImp() = default;

  /**\return bit mask of pressed buttons
   */
  virtual Mouse::Buttons buttons() const = 0;

  virtual Point currentPos() const  = 0;
  virtual Point previousPos() const = 0;
};
} // namespace KaliLaska
