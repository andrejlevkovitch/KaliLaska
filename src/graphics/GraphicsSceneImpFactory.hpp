// GraphicsSceneImpFactory.hpp

#pragma once

#include <memory>

namespace KaliLaska {
class GraphicsSceneImp;

class GraphicsSceneImpFactory {
public:
  static std::unique_ptr<GraphicsSceneImp> createImp();
};
} // namespace KaliLaska
