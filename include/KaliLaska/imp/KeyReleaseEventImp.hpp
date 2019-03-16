// KeyReleaseEventImp.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "kalilaska_export.h"

namespace KaliLaska {
class KALILASKA_EXPORT KeyReleaseEventImp {
public:
  virtual ~KeyReleaseEventImp() = default;

  virtual Keyboard::Modifyers modifyers() const = 0;
  virtual Keyboard::Key       key() const       = 0;
};
} // namespace KaliLaska
