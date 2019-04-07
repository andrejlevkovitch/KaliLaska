// Point.hpp

#pragma once

#include "kalilaska_export.h"
#include <boost/geometry/geometries/point_xy.hpp>
#include <ostream>

namespace KaliLaska {
/**\brief boost certesian (int) point
 * \warning if not initialized - contain garbage
 */
using Point = boost::geometry::model::d2::point_xy<int>;

/**\brief boost certesian (float) point
 * \warning if not initialized - contain garbage
 */
using PointF =
    boost::geometry::model::point<float, 2, boost::geometry::cs::cartesian>;

} // namespace KaliLaska

KALILASKA_EXPORT bool operator==(const KaliLaska::Point &lhs,
                                 const KaliLaska::Point &rhs);
KALILASKA_EXPORT bool operator!=(const KaliLaska::Point &lhs,
                                 const KaliLaska::Point &rhs);

KALILASKA_EXPORT bool operator==(const KaliLaska::PointF &lhs,
                                 const KaliLaska::PointF &rhs);
KALILASKA_EXPORT bool operator!=(const KaliLaska::PointF &lhs,
                                 const KaliLaska::PointF &rhs);

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &          stream,
                                          const KaliLaska::Point &point);
KALILASKA_EXPORT std::ostream &operator<<(std::ostream &           stream,
                                          const KaliLaska::PointF &point);

KaliLaska::Point operator+(const KaliLaska::Point &lhs,
                           const KaliLaska::Point &rhs);

KaliLaska::Point operator-(const KaliLaska::Point &lhs,
                           const KaliLaska::Point &rhs);

KaliLaska::PointF operator+(const KaliLaska::PointF &lhs,
                            const KaliLaska::PointF &rhs);

KaliLaska::PointF operator-(const KaliLaska::PointF &lhs,
                            const KaliLaska::PointF &rhs);
