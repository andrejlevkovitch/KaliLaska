// GraphicsSceneImpFactory.hpp

#pragma once

#include <memory>

namespace KaliLaska {
class GraphicsSceneImp;

class GraphicsSceneImpFactory {
public:
  virtual ~GraphicsSceneImpFactory() = default;
  virtual std::unique_ptr<GraphicsSceneImp> createGraphicsScene() const = 0;
};
} // namespace KaliLaska
