// Point.cpp

#include "KaliLaska/Point.hpp"
#include <boost/geometry.hpp>

namespace bg = boost::geometry;

KaliLaska::PointF operator+(const KaliLaska::PointF &lhs,
                            const KaliLaska::PointF &rhs) {
  KaliLaska::PointF retval = lhs;
  bg::add_point(retval, rhs);
  return retval;
}

KaliLaska::PointF operator-(const KaliLaska::PointF &lhs,
                            const KaliLaska::PointF &rhs) {
  KaliLaska::PointF retval = lhs;
  bg::subtract_point(retval, rhs);
  return retval;
}

KaliLaska::Point operator+(const KaliLaska::Point &lhs,
                           const KaliLaska::Point &rhs) {
  KaliLaska::Point retval = lhs;
  bg::add_point(retval, rhs);
  return retval;
}

KaliLaska::Point operator-(const KaliLaska::Point &lhs,
                           const KaliLaska::Point &rhs) {
  KaliLaska::Point retval = lhs;
  bg::subtract_point(retval, rhs);
  return retval;
}

bool operator==(const KaliLaska::Point &lhs, const KaliLaska::Point &rhs) {
  return boost::geometry::equals(lhs, rhs);
}

bool operator!=(const KaliLaska::Point &lhs, const KaliLaska::Point &rhs) {
  return !boost::geometry::equals(lhs, rhs);
}

std::ostream &operator<<(std::ostream &stream, const KaliLaska::Point &point) {
  stream << bg::wkt(point);
  return stream;
}

bool operator==(const KaliLaska::PointF &lhs, const KaliLaska::PointF &rhs) {
  return boost::geometry::equals(lhs, rhs);
}

bool operator!=(const KaliLaska::PointF &lhs, const KaliLaska::PointF &rhs) {
  return !boost::geometry::equals(lhs, rhs);
}

std::ostream &operator<<(std::ostream &stream, const KaliLaska::PointF &point) {
  stream << bg::wkt(point);
  return stream;
}
