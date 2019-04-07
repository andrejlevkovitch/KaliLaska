// TransformMatrix.cpp

#include "KaliLaska/TransformMatrix.hpp"
#include <boost/geometry.hpp>

namespace bq = boost::qvm;
namespace bg = boost::geometry;

namespace KaliLaska {
float getAngle(const TransformMatrix &mat) {
  auto [xFactor, yFactor] = getScale(mat);
  auto sinAngl =
      bq::mat_traits<TransformMatrix>::read_element<0, 1>(mat) / yFactor;
  auto cosAngl =
      bq::mat_traits<TransformMatrix>::read_element<0, 0>(mat) / xFactor;
  return std::atan2(-sinAngl, cosAngl);
}

std::pair<float, float> getScale(const TransformMatrix &mat) {
  PointF xVec{bq::mat_traits<TransformMatrix>::read_element<0, 0>(mat),
              bq::mat_traits<TransformMatrix>::read_element<1, 0>(mat)};
  PointF yVec{bq::mat_traits<TransformMatrix>::read_element<0, 1>(mat),
              bq::mat_traits<TransformMatrix>::read_element<1, 1>(mat)};

  return {bg::length(bg::model::linestring<PointF>{{0, 0}, xVec}),
          bg::length(bg::model::linestring<PointF>{{0, 0}, yVec})};
}

PointF getTranslation(const TransformMatrix &mat) {
  return {bq::mat_traits<TransformMatrix>::read_element<0, 2>(mat),
          bq::mat_traits<TransformMatrix>::read_element<1, 2>(mat)};
}

TransformMatrix getRotaionMat(const TransformMatrix &mat) {
  auto [xFactor, yFactor] = getScale(mat);

  // clang-format off
  return {{{bq::mat_traits<TransformMatrix>::read_element<0, 0>(mat) / xFactor,
            bq::mat_traits<TransformMatrix>::read_element<0, 1>(mat) / yFactor,
            0},
           {bq::mat_traits<TransformMatrix>::read_element<1, 0>(mat) / xFactor,
            bq::mat_traits<TransformMatrix>::read_element<1, 1>(mat) / yFactor,
            0},
           {0, 0, 1}}};
  // clang-format on
}

TransformMatrix getScaleMat(const TransformMatrix &mat) {
  auto [xFactor, yFactor] = getScale(mat);

  // clang-format off
  return {{{xFactor, 0, 0},
           {0, yFactor, 0},
           {0, 0, 1}}};
  // clang-format on
}

TransformMatrix getTranslationMat(const TransformMatrix &mat) {
  // clang-format on
  return {{{1, 0, bq::mat_traits<TransformMatrix>::read_element<0, 2>(mat)},
           {0, 1, bq::mat_traits<TransformMatrix>::read_element<1, 2>(mat)},
           {0, 0, 1}}};
  // clang-format off
}

float toRad(float angle) {
  return angle * 3.14 / 180;
}

float toDegrees(float angle) {
  return angle * 180 / 3.14;
}
} // namespace KaliLaska
