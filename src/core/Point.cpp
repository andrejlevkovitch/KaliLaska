// Point.cpp

#include "KaliLaska/Point.hpp"
#include <boost/geometry.hpp>

bool operator==(const KaliLaska::Point &lhs, const KaliLaska::Point &rhs) {
  return (lhs.x() == rhs.x() && lhs.y() == rhs.y());
}

bool operator!=(const KaliLaska::Point &lhs, const KaliLaska::Point &rhs) {
  return (lhs.x() != rhs.x() || lhs.y() != rhs.y());
}

std::ostream &operator<<(std::ostream &stream, const KaliLaska::Point &point) {
  stream << "x " << point.x() << ", y " << point.y();
  return stream;
}
