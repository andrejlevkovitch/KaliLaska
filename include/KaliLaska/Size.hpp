// Size.hpp

#pragma once

#include "KaliLaska/kalilaska_export.h"
#include <ostream>

namespace KaliLaska {
class KALILASKA_EXPORT Size {
public:
  Size();
  Size(int width, int height);

  int width() const;
  int height() const;

  void setWidth(int width);
  void setHeight(int height);

private:
  int width_;
  int height_;
};

std::ostream &operator<<(std::ostream &stream, const Size &size);
} // namespace KaliLaska
