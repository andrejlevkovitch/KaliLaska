// GraphicsSceneRTreeFactory.hpp

#pragma once

#include "graphics/imp/GraphicsSceneImpFactory.hpp"

namespace KaliLaska {
class GraphicsSceneRTreeFactory final : public GraphicsSceneImpFactory {
public:
  std::unique_ptr<GraphicsSceneImp> createGraphicsSceneImp() override;
};
} // namespace KaliLaska
