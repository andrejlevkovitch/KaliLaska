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
  stream << "Point: x " << point.x() << ", y " << point.y();
  return stream;
}

bool operator==(const KaliLaska::PointF &lhs, const KaliLaska::PointF &rhs) {
  return boost::geometry::equals(lhs, rhs);
}

bool operator!=(const KaliLaska::PointF &lhs, const KaliLaska::PointF &rhs) {
  return !boost::geometry::equals(lhs, rhs);
}

std::ostream &operator<<(std::ostream &stream, const KaliLaska::PointF &point) {
  stream << "Point: x " << boost::geometry::get<0>(point) << ", y "
         << boost::geometry::get<1>(point);
  return stream;
}
