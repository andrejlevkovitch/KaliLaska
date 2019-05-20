// GraphicsSceneRTreeFactory.cpp

#include "GraphicsSceneRTreeFactory.hpp"
#include "GraphicsSceneRTree.hpp"

namespace KaliLaska {
std::unique_ptr<GraphicsSceneImp>
GraphicsSceneRTreeFactory::createGraphicsSceneImp() {
  return std::make_unique<GraphicsSceneRTree>();
}
} // namespace KaliLaska
