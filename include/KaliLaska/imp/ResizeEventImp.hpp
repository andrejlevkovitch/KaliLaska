// ResizeEventImp.hpp

#pragma once

#include "KaliLaska/Size.hpp"

namespace KaliLaska {
class ResizeEventImp {
public:
  virtual ~ResizeEventImp() = default;

  virtual Size previousSize() const = 0;
  virtual Size newSize() const      = 0;
};
} // namespace KaliLaska
