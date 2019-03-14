// ShowEventImp.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/kalilaska_export.h"

namespace KaliLaska {
class KALILASKA_EXPORT ShowEventImp {
public:
  virtual ~ShowEventImp()           = default;
  virtual ShowAction action() const = 0;
};
} // namespace KaliLaska
