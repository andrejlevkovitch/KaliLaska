// ResizeEventImp.hpp

#pragma once

#include "KaliLaska/Size.hpp"
#include "KaliLaska/kalilaska_export.h"

namespace KaliLaska {
class KALILASKA_EXPORT ResizeEventImp {
public:
  virtual ~ResizeEventImp() = default;

  virtual Size previousSize() const = 0;
  virtual Size newSize() const      = 0;
};
} // namespace KaliLaska
