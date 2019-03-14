// MouseFocusEventImp.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "kalilaska_export.h"

namespace KaliLaska {
class KALILASKA_EXPORT MouseFocusEventImp {
public:
  virtual ~MouseFocusEventImp() = default;

  virtual Mouse::Focus focus() const = 0;
};
} // namespace KaliLaska
