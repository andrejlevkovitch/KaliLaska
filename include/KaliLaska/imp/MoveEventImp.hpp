// MoveEventImp.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"

namespace KaliLaska {
class MoveEventImp {
public:
  virtual ~MoveEventImp() = default;

  virtual Point currentPos() const = 0;
};
} // namespace KaliLaska
