// KeyReleaseEventImp.hpp

#pragma once

#include "KaliLaska/Event.hpp"

namespace KaliLaska {
class KeyReleaseEventImp {
public:
  virtual ~KeyReleaseEventImp() = default;

  virtual Keyboard::Modifyers modifyers() const = 0;
  virtual Keyboard::Key       key() const       = 0;
};
} // namespace KaliLaska
