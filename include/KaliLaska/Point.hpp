// Point.hpp

#pragma once

#include <ostream>

namespace KaliLaska {
class Point {
public:
  Point();
  Point(int x, int y);

  int x() const;
  int y() const;

  void setX(int x);
  void setY(int y);

private:
  int x_;
  int y_;
};

std::ostream &operator<<(std::ostream &stream, const Point &point);
} // namespace KaliLaska
