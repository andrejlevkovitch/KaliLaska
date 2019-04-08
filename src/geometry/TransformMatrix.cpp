// TransformMatrix.cpp

#include "KaliLaska/TransformMatrix.hpp"
#include <boost/geometry.hpp>

namespace bq = boost::qvm;
namespace bg = boost::geometry;

namespace KaliLaska {
// here we not check on 0 because the values in valid matrix can not be 0,
// otherwise it is not valid matrix
float getAngle(const TransformMatrix &mat) {
  auto [xFactor, yFactor] = getScale(mat);
  auto sinAngl =
      bq::mat_traits<TransformMatrix>::read_element<0, 1>(mat) / yFactor;
  auto cosAngl =
      bq::mat_traits<TransformMatrix>::read_element<0, 0>(mat) / xFactor;
  return std::atan2(-sinAngl, cosAngl);
}

std::pair<float, float> getScale(const TransformMatrix &mat) {
  std::pair<float, float> xVec{
      bq::mat_traits<TransformMatrix>::read_element<0, 0>(mat),
      bq::mat_traits<TransformMatrix>::read_element<1, 0>(mat)};
  std::pair<float, float> yVec{
      bq::mat_traits<TransformMatrix>::read_element<0, 1>(mat),
      bq::mat_traits<TransformMatrix>::read_element<1, 1>(mat)};

  return {std::sqrt(std::pow(xVec.first, 2) + std::pow(xVec.second, 2)),
          std::sqrt(std::pow(yVec.first, 2) + std::pow(yVec.second, 2))};
}

PointF getTranslation(const TransformMatrix &mat) {
  return {bq::mat_traits<TransformMatrix>::read_element<0, 2>(mat),
          bq::mat_traits<TransformMatrix>::read_element<1, 2>(mat)};
}

// here we not check on 0 because the values in valid matrix can not be 0,
// otherwise it is not valid matrix
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
  return {{{xFactor, 0,       0},
           {0,       yFactor, 0},
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

std::ostream &operator<<(std::ostream &stream, const KaliLaska::TransformMatrix &mat) {
  stream <<
    bq::mat_traits<KaliLaska::TransformMatrix>::read_element<0, 0>(mat) << ' ' <<
    bq::mat_traits<KaliLaska::TransformMatrix>::read_element<0, 1>(mat) << ' ' <<
    bq::mat_traits<KaliLaska::TransformMatrix>::read_element<0, 2>(mat) << std::endl <<
    bq::mat_traits<KaliLaska::TransformMatrix>::read_element<1, 0>(mat) << ' ' <<
    bq::mat_traits<KaliLaska::TransformMatrix>::read_element<1, 1>(mat) << ' ' <<
    bq::mat_traits<KaliLaska::TransformMatrix>::read_element<1, 2>(mat) << std::endl <<
    bq::mat_traits<KaliLaska::TransformMatrix>::read_element<2, 0>(mat) << ' ' <<
    bq::mat_traits<KaliLaska::TransformMatrix>::read_element<2, 1>(mat) << ' ' <<
    bq::mat_traits<KaliLaska::TransformMatrix>::read_element<2, 2>(mat);
  return stream;
}
