// GraphicsSceneImpFactory.cpp

#include "GraphicsSceneImpFactory.hpp"
#include "graphics/rtree/GraphicsSceneRTree.hpp"

namespace KaliLaska {
std::unique_ptr<GraphicsSceneImp> GraphicsSceneImpFactory::createImp() {
  return std::unique_ptr<GraphicsSceneRTree>();
}
} // namespace KaliLaska
