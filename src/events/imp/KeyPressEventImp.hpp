// KeyPressEventImp.hpp

#pragma once

#include "KaliLaska/Event.hpp"

namespace KaliLaska {
class KeyPressEventImp {
public:
  virtual ~KeyPressEventImp() = default;

  virtual Keyboard::Key       key() const       = 0;
  virtual Keyboard::Modifyers modifyers() const = 0;
  virtual bool                isRepeat() const  = 0;
};
} // namespace KaliLaska
