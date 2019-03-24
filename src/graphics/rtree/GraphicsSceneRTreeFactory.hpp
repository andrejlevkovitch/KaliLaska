// GraphicsSceneRTreeFactory.hpp

#pragma once

#include "graphics/imp/GraphicsSceneImpFactory.hpp"

namespace KaliLaska {
class GraphicsSceneRTreeFactory final : public GraphicsSceneImpFactory {
public:
  ~GraphicsSceneRTreeFactory() = default;
  std::unique_ptr<GraphicsSceneImp> createGraphicsScene() const override;
};
} // namespace KaliLaska
