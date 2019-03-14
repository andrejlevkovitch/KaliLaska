// MouseReleaseEventImp.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"
#include "KaliLaska/kalilaska_export.h"

namespace KaliLaska {
class KALILASKA_EXPORT MouseReleaseEventImp {
public:
  virtual ~MouseReleaseEventImp() = default;

  virtual Mouse::Button  button() const   = 0;
  virtual Mouse::Buttons buttons() const  = 0;
  virtual Point          clickPos() const = 0;
};
} // namespace KaliLaska
