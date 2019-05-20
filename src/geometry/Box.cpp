// Box.cpp

#include "KaliLaska/Box.hpp"
#include <boost/geometry.hpp>

namespace bg = boost::geometry;

bool operator==(const KaliLaska::Box &lhs, const KaliLaska::Box &rhs) {
  return bg::equals(lhs, rhs);
}

bool operator!=(const KaliLaska::Box &lhs, const KaliLaska::Box &rhs) {
  return !bg::equals(lhs, rhs);
}

std::ostream &operator<<(std::ostream &stream, const KaliLaska::Box &box) {
  stream << bg::wkt(box);
  return stream;
}
