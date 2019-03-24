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

} // namespace KaliLaska

KALILASKA_EXPORT bool operator==(const KaliLaska::Point &lhs,
                                 const KaliLaska::Point &rhs);
KALILASKA_EXPORT bool operator!=(const KaliLaska::Point &lhs,
                                 const KaliLaska::Point &rhs);

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &          stream,
                                          const KaliLaska::Point &point);
