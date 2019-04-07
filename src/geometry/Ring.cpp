// Ring.cpp

#include "KaliLaska/Ring.hpp"
#include <boost/geometry.hpp>
#include <cstdint>
#include <list>

namespace bg = boost::geometry;

namespace KaliLaska {
std::vector<unsigned short> triangulation(const Ring &ring) {
  std::vector<unsigned short> retval;
  if (!bg::is_valid(ring) || ring.size() < 4) {
    return retval;
  }

  // reserve memory for retval
  retval.reserve((ring.size() - 1) * 3);

  std::list<unsigned short> points;
  for (size_t i{}; i < ring.size() - 1; ++i) {
    points.push_back(i);
  }

  // ear - have to be valid iterator of points
  auto getTriangleWithEar = [&ring, &points](const auto &ear) {
    uint16_t earVertex = *ear;
    uint16_t lhsVertex{};
    uint16_t rhsVertex{};

    if (ear == points.begin()) {
      lhsVertex = *points.rbegin();
    } else {
      lhsVertex = *std::prev(ear);
    }

    if (auto next = std::next(ear); next == points.end()) {
      rhsVertex = *points.begin();
    } else {
      rhsVertex = *next;
    }

    return std::pair{
        Ring{
            ring[lhsVertex], ring[earVertex], ring[rhsVertex], ring[lhsVertex]},
        std::array<uint16_t, 3>{lhsVertex, earVertex, rhsVertex}};
  };

  static const bg::de9im::mask withinMask{"T*F**F***"}; // within

  auto curIterator = points.begin();

  // brief if causes some error the cickle have to stop
  bool noOneEar{true};

  // because at end in the ring have to be only one triangle + 1 end point,
  // which is first point to
  while (points.size() > 3) {
    if (curIterator == points.end()) {
      // in case if some error happens
      if (noOneEar) {
        break;
      } else {
        curIterator = points.begin();
        noOneEar    = true;
      }
    }

    auto [curTriangle, indexes] = getTriangleWithEar(curIterator);
    // brief if triangle in ring, then add to retval, otherwise just look next
    if (bg::relate(curTriangle, ring, withinMask)) {
      std::copy(indexes.begin(), indexes.end(), std::back_inserter(retval));
      curIterator = points.erase(curIterator);
      noOneEar    = false;
    } else {
      ++curIterator;
    }
  }

  // append last triangle
  if (!noOneEar) {
    std::copy(points.begin(), points.end(), std::back_inserter(retval));
  }

  return retval;
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &stream, const KaliLaska::Ring &ring) {
  stream << bg::wkt(ring);
  return stream;
}

