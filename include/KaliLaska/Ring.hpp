// Ring.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include <boost/geometry/geometries/ring.hpp>

namespace KaliLaska {
using Ring = boost::geometry::model::ring<PointF>;

/**\param ring must be valid ring with 4 or more points
 * \return vector of points numbers in the ring which is triangles, or void
 * vector if causes some problems
 */
std::vector<unsigned short> triangulation(const Ring &ring);
} // namespace KaliLaska

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &         stream,
                                          const KaliLaska::Ring &ring);
