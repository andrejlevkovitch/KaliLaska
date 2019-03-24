// Size.hpp

#pragma once

#include "kalilaska_export.h"
#include <ostream>

namespace KaliLaska {
class KALILASKA_EXPORT Size final {
public:
  Size();
  Size(int width, int height);

  int width() const;
  int height() const;

  void setWidth(int width);
  void setHeight(int height);

  bool operator!=(const Size &rhs) const;
  bool operator==(const Size &rhs) const;

private:
  int width_;
  int height_;
};
} // namespace KaliLaska

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &         stream,
                                          const KaliLaska::Size &size);
