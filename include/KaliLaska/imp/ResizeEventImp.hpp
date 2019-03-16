// ResizeEventImp.hpp

#pragma once

#include "KaliLaska/Size.hpp"
#include "kalilaska_export.h"

namespace KaliLaska {
class KALILASKA_EXPORT ResizeEventImp {
public:
  virtual ~ResizeEventImp() = default;

  virtual Size currentSize() const = 0;
};
} // namespace KaliLaska
