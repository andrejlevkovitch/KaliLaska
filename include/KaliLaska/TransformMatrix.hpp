// TransformMatrix.hpp

#pragma once

#include <boost/geometry/strategies/transform/matrix_transformers.hpp>

namespace KaliLaska {
using TransformMatrix =
    boost::geometry::strategy::transform::matrix_transformer<float, 2, 2>;
} // namespace KaliLaska
