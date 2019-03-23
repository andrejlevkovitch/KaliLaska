// ShowEventImp.hpp

#pragma once

#include "KaliLaska/Event.hpp"

namespace KaliLaska {
class ShowEventImp {
public:
  virtual ~ShowEventImp()           = default;
  virtual ShowAction action() const = 0;
};
} // namespace KaliLaska
