// Point.hpp

#pragma once

#include "kalilaska_export.h"
#include <ostream>

namespace KaliLaska {
class KALILASKA_EXPORT Point {
public:
  Point();
  Point(int x, int y);

  int x() const;
  int y() const;

  void setX(int x);
  void setY(int y);

  bool operator!=(const Point &rhs) const;
  bool operator==(const Point &rhs) const;

private:
  int x_;
  int y_;
};

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &stream,
                                          const Point & point);
} // namespace KaliLaska
