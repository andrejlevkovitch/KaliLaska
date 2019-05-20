// Box.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include "kalilaska_export.h"
#include <boost/geometry/geometries/box.hpp>

namespace KaliLaska {
/**\brief boost certesian box
 * \warning if not initialized - contain garbage
 */
using Box = boost::geometry::model::box<PointF>;
} // namespace KaliLaska

/**\return true if boxes are identical
 */
KALILASKA_EXPORT bool operator==(const KaliLaska::Box &lhs,
                                 const KaliLaska::Box &rhs);

KALILASKA_EXPORT bool operator!=(const KaliLaska::Box &lhs,
                                 const KaliLaska::Box &rhs);

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &        stream,
                                          const KaliLaska::Box &box);
