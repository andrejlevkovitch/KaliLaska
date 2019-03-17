// Point.cpp

#include "KaliLaska/Point.hpp"

namespace KaliLaska {

Point::Point()
    : x_{}
    , y_{} {
}

Point::Point(int x, int y)
    : x_{x}
    , y_{y} {
}

int Point::x() const {
  return x_;
}

int Point::y() const {
  return y_;
}

void Point::setX(int x) {
  x_ = x;
}

void Point::setY(int y) {
  y_ = y;
}

bool Point::operator!=(const Point &rhs) const {
  return (x_ != rhs.x_ || y_ != rhs.y_);
}

bool Point::operator==(const Point &rhs) const {
  return (x_ == rhs.x_ && y_ == rhs.y_);
}

std::ostream &operator<<(std::ostream &stream, const Point &point) {
  stream << "x " << point.x() << ", y " << point.y();
  return stream;
}
} // namespace KaliLaska
