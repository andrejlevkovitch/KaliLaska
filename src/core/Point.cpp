// Point.cpp

#include "KaliLaska/Point.hpp"
#include <boost/geometry.hpp>

bool operator==(const KaliLaska::Point &lhs, const KaliLaska::Point &rhs) {
  return boost::geometry::equals(lhs, rhs);
}

bool operator!=(const KaliLaska::Point &lhs, const KaliLaska::Point &rhs) {
  return !boost::geometry::equals(lhs, rhs);
}

std::ostream &operator<<(std::ostream &stream, const KaliLaska::Point &point) {
  stream << "x " << point.x() << ", y " << point.y();
  return stream;
}
