// Box.cpp

#include "KaliLaska/Box.hpp"
#include <boost/geometry.hpp>

bool operator==(const KaliLaska::Box &lhs, const KaliLaska::Box &rhs) {
  return boost::geometry::equals(lhs, rhs);
}

bool operator!=(const KaliLaska::Box &lhs, const KaliLaska::Box &rhs) {
  return !boost::geometry::equals(lhs, rhs);
}

std::ostream &operator<<(std::ostream &stream, const KaliLaska::Box &box) {
  stream << "Box: " << box.min_corner() << ", " << box.max_corner();
  return stream;
}
