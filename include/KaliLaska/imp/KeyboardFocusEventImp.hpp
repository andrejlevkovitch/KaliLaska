// KeyboardFocusEventImp.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "kalilaska_export.h"

namespace KaliLaska {
class KALILASKA_EXPORT KeyboardFocusEventImp {
public:
  virtual ~KeyboardFocusEventImp() = default;

  virtual Keyboard::Focus focus() const = 0;

private:
};
} // namespace KaliLaska
