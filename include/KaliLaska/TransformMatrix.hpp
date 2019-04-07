// TransformMatrix.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include <boost/qvm/mat.hpp>

namespace KaliLaska {
using TransformMatrix = boost::qvm::mat<float, 3, 3>;

/**\return angle in radians
 */
float                   getAngle(const TransformMatrix &mat);
std::pair<float, float> getScale(const TransformMatrix &mat);
PointF                  getTranslation(const TransformMatrix &mat);

TransformMatrix getRotaionMat(const TransformMatrix &mat);
TransformMatrix getScaleMat(const TransformMatrix &mat);
TransformMatrix getTranslationMat(const TransformMatrix &mat);

float toRad(float angle);

float toDegrees(float angle);
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &                    stream,
                         const KaliLaska::TransformMatrix &mat);
