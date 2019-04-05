// test_triangulation.cpp

#define CATCH_CONFIG_MAIN

#include "KaliLaska/Ring.hpp"
#include <boost/geometry.hpp>
#include <catch2/catch.hpp>

namespace bg = boost::geometry;

static const bg::de9im::mask withinMask{"T*F**F***"}; // within

SCENARIO("Test triangulation funcion", "[triangulation]") {
  GIVEN("not complete ring") {
    KaliLaska::Ring ring{{0, 1}, {2, 0}, {0, 1}};
    WHEN("we try triangulation") {
      auto retval = KaliLaska::triangulation(ring);
      THEN("we have to get empty retval") { CHECK(retval.empty()); }
    }
  }

  GIVEN("not valid ring") {
    KaliLaska::Ring ring{{0, 0}, {5, 0}, {5, 5}, {0, 5}, {0, 0}};
    WHEN("we try triangulation") {
      auto retval = KaliLaska::triangulation(ring);
      THEN("we have to get empty retval") { CHECK(retval.empty()); }
    }
  }

  GIVEN("valid ring which describe quadr") {
    KaliLaska::Ring ring;
    bg::read_wkt("POLYGON((0 0, 0 5, 5 5, 5 0, 0 0))", ring);
    WHEN("we try triangulation") {
      auto retval = KaliLaska::triangulation(ring);
      THEN("we have to get right rezult") {
        REQUIRE(retval.size() == 2 * 3);
        for (size_t i{}; i < retval.size(); i += 3) {
          CHECK(bg::relate(KaliLaska::Ring{ring[retval[i]],
                                           ring[retval[i + 1]],
                                           ring[retval[i + 2]],
                                           ring[retval[i]]},
                           ring,
                           withinMask));
        }
      }
    }
  }

  GIVEN("big valid ring") {
    KaliLaska::Ring ring;
    bg::read_wkt("POLYGON((7 0, 3 0, 5 3, 0 5, 4 6, 0 11, 7 11, 8 10, 9 11, 14 "
                 "11, 12 6, 17 0, 12 0, 9 3, 7 0))",
                 ring);
    WHEN("we try triangulation") {
      auto retval = KaliLaska::triangulation(ring);
      THEN("we have to get right rezult") {
        REQUIRE_FALSE(retval.empty());
        for (size_t i{}; i < retval.size(); i += 3) {
          CHECK(bg::relate(KaliLaska::Ring{ring[retval[i]],
                                           ring[retval[i + 1]],
                                           ring[retval[i + 2]],
                                           ring[retval[i]]},
                           ring,
                           withinMask));
        }
      }
    }
  }
}
