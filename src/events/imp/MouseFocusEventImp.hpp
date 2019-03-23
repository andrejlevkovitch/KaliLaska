// MouseFocusEventImp.hpp

#pragma once

#include "KaliLaska/Event.hpp"

namespace KaliLaska {
class MouseFocusEventImp {
public:
  virtual ~MouseFocusEventImp() = default;

  virtual Mouse::Focus focus() const = 0;
};
} // namespace KaliLaska
