// GraphicSceneRTreeFactory.cpp

#include "GraphicsSceneRTreeFactory.hpp"
#include "GraphicsSceneRTree.hpp"

namespace KaliLaska {
std::unique_ptr<GraphicsSceneImp>
GraphicsSceneRTreeFactory::createGraphicsScene() const {
  return std::make_unique<GraphicsSceneRTree>();
}
} // namespace KaliLaska
