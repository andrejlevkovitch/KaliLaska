// KeyboardFocusEventImp.hpp

#pragma once

#include "KaliLaska/Event.hpp"

namespace KaliLaska {
class KeyboardFocusEventImp {
public:
  virtual ~KeyboardFocusEventImp() = default;

  virtual Keyboard::Focus focus() const = 0;

private:
};
} // namespace KaliLaska
