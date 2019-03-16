// KeyPressEventImp.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "kalilaska_export.h"

namespace KaliLaska {
class KALILASKA_EXPORT KeyPressEventImp {
public:
  virtual ~KeyPressEventImp() = default;

  virtual Keyboard::Key       key() const       = 0;
  virtual Keyboard::Modifyers modifyers() const = 0;
  virtual bool                isRepeat() const  = 0;
};
} // namespace KaliLaska
