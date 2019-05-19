// test_TransformMatrix.cpp

#define CATCH_CONFIG_MAIN

#include "KaliLaska/TransformMatrix.hpp"
#include <boost/qvm/mat_operations.hpp>
#include <catch2/catch.hpp>

namespace bq = boost::qvm;
namespace bg = boost::geometry;

#define COMPARE_MAT(x, y)                                                      \
  CHECK(bq::mat_traits<KaliLaska::TransformMatrix>::read_element<0, 0>(x) ==   \
        Approx(                                                                \
            bq::mat_traits<KaliLaska::TransformMatrix>::read_element<0, 0>(y)) \
            .epsilon(0.01));                                                   \
  CHECK(bq::mat_traits<KaliLaska::TransformMatrix>::read_element<0, 1>(x) ==   \
        Approx(                                                                \
            bq::mat_traits<KaliLaska::TransformMatrix>::read_element<0, 1>(y)) \
            .epsilon(0.01));                                                   \
  CHECK(bq::mat_traits<KaliLaska::TransformMatrix>::read_element<0, 2>(x) ==   \
        Approx(                                                                \
            bq::mat_traits<KaliLaska::TransformMatrix>::read_element<0, 2>(y)) \
            .epsilon(0.01));                                                   \
  CHECK(bq::mat_traits<KaliLaska::TransformMatrix>::read_element<1, 0>(x) ==   \
        Approx(                                                                \
            bq::mat_traits<KaliLaska::TransformMatrix>::read_element<1, 0>(y)) \
            .epsilon(0.01));                                                   \
  CHECK(bq::mat_traits<KaliLaska::TransformMatrix>::read_element<1, 1>(x) ==   \
        Approx(                                                                \
            bq::mat_traits<KaliLaska::TransformMatrix>::read_element<1, 1>(y)) \
            .epsilon(0.01));                                                   \
  CHECK(bq::mat_traits<KaliLaska::TransformMatrix>::read_element<1, 2>(x) ==   \
        Approx(                                                                \
            bq::mat_traits<KaliLaska::TransformMatrix>::read_element<1, 2>(y)) \
            .epsilon(0.01));                                                   \
  CHECK(bq::mat_traits<KaliLaska::TransformMatrix>::read_element<2, 0>(x) ==   \
        Approx(                                                                \
            bq::mat_traits<KaliLaska::TransformMatrix>::read_element<2, 0>(y)) \
            .epsilon(0.01));                                                   \
  CHECK(bq::mat_traits<KaliLaska::TransformMatrix>::read_element<2, 1>(x) ==   \
        Approx(                                                                \
            bq::mat_traits<KaliLaska::TransformMatrix>::read_element<2, 1>(y)) \
            .epsilon(0.01));                                                   \
  CHECK(bq::mat_traits<KaliLaska::TransformMatrix>::read_element<2, 2>(x) ==   \
        Approx(                                                                \
            bq::mat_traits<KaliLaska::TransformMatrix>::read_element<2, 2>(y)) \
            .epsilon(0.01));

SCENARIO("test matrix operations", "[TransformMatrix]") {
  GIVEN("simple matrix") {
    // clang-format off
    KaliLaska::TransformMatrix mat{{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    }};
    // clang-format on

    WHEN("We set position to matrix") {
      KaliLaska::PointF pos{1890, 3456};
      bq::mat_traits<KaliLaska::TransformMatrix>::write_element<0, 2>(mat) =
          bg::get<0>(pos);
      bq::mat_traits<KaliLaska::TransformMatrix>::write_element<1, 2>(mat) =
          bg::get<1>(pos);

      THEN("We have to get from matrix the value") {
        auto getPos = KaliLaska::getTranslation(mat);
        CHECK(bg::get<0>(getPos) == Approx(bg::get<0>(pos)).epsilon(0.01));
        CHECK(bg::get<1>(getPos) == Approx(bg::get<1>(pos)).epsilon(0.01));
      }
    }

    WHEN("We set scale to matrix") {
      std::pair<float, float> scale{5.6, 8.2};
      bq::mat_traits<KaliLaska::TransformMatrix>::write_element<0, 0>(mat) =
          scale.first;
      bq::mat_traits<KaliLaska::TransformMatrix>::write_element<1, 1>(mat) =
          scale.second;

      THEN("We have to get from matrix the value") {
        auto getScale = KaliLaska::getScale(mat);
        CHECK(getScale.first == Approx(scale.first).epsilon(0.01));
        CHECK(getScale.second == Approx(scale.second).epsilon(0.01));
      }
    }

    WHEN("We set rotation (radians) to matrix") {
      float angle{1.56};
      bq::mat_traits<KaliLaska::TransformMatrix>::write_element<0, 0>(mat) =
          std::cos(angle);
      bq::mat_traits<KaliLaska::TransformMatrix>::write_element<1, 1>(mat) =
          std::cos(angle);
      bq::mat_traits<KaliLaska::TransformMatrix>::write_element<0, 1>(mat) =
          -std::sin(angle);
      bq::mat_traits<KaliLaska::TransformMatrix>::write_element<1, 0>(mat) =
          std::sin(angle);

      THEN("We have to get from matrix the value") {
        auto getAngle = KaliLaska::getRotation(mat);
        CHECK(getAngle == Approx(angle).epsilon(0.01));
      }
    }

    WHEN("We set complex (translate, scale, rotation)") {
      // in radians
      float angle{1.8};

      // clang-format off
      KaliLaska::TransformMatrix translate{{
          {1, 0, 3875},
          {0, 1, 9890},
          {0, 0, 1}
      }};
      KaliLaska::TransformMatrix rotation{{
          {std::cos(angle), -std::sin(angle), 0},
          {std::sin(angle), std::cos(angle), 0},
          {0, 0, 1}
      }};
      KaliLaska::TransformMatrix scale{{
          {1.9, 0,   0},
          {0,   4.9, 0},
          {0,   0,   1}
      }};
      // clang-format on

      // here we first rotate and second scale!!!
      mat *= translate;
      mat *= rotation;
      mat *= scale;

      // clang-format off
      std::cerr <<
        bq::mat_traits<KaliLaska::TransformMatrix>::read_element<0, 0>(mat) << ' ' <<
        bq::mat_traits<KaliLaska::TransformMatrix>::read_element<0, 1>(mat) << ' ' <<
        bq::mat_traits<KaliLaska::TransformMatrix>::read_element<0, 2>(mat) << std::endl <<
        bq::mat_traits<KaliLaska::TransformMatrix>::read_element<1, 0>(mat) << ' ' <<
        bq::mat_traits<KaliLaska::TransformMatrix>::read_element<1, 1>(mat) << ' ' <<
        bq::mat_traits<KaliLaska::TransformMatrix>::read_element<1, 2>(mat) << std::endl <<
        bq::mat_traits<KaliLaska::TransformMatrix>::read_element<2, 0>(mat) << ' ' <<
        bq::mat_traits<KaliLaska::TransformMatrix>::read_element<2, 1>(mat) << ' ' <<
        bq::mat_traits<KaliLaska::TransformMatrix>::read_element<2, 2>(mat) << std::endl;

      // clang-format on

      THEN("Check get translate mat") {
        auto getTrMat = KaliLaska::getTranslationMat(mat);

        COMPARE_MAT(getTrMat, translate);
      }
      AND_THEN("Check get scale mat") {
        auto getScaleMat = KaliLaska::getScaleMat(mat);

        COMPARE_MAT(getScaleMat, scale);
      }
      AND_THEN("Check get rotation mat") {
        auto getRotMat = KaliLaska::getRotationMat(mat);

        COMPARE_MAT(getRotMat, rotation);
        CHECK(angle == Approx(KaliLaska::getRotation(mat)).epsilon(0.01));
      }

      WHEN("We multiplication all geted matrix to one") {
        auto getTrMat    = KaliLaska::getTranslationMat(mat);
        auto getScaleMat = KaliLaska::getScaleMat(mat);
        auto getRotMat   = KaliLaska::getRotationMat(mat);

        // clang-format off
        KaliLaska::TransformMatrix multiMat{{
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
        }};
        // clang-format on

        multiMat *= getTrMat;
        multiMat *= getRotMat;
        multiMat *= getScaleMat;

        THEN("Compare it with our general mat") { COMPARE_MAT(multiMat, mat); }
      }
    }
  }
}
