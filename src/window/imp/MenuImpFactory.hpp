// MenuImpFactory.hpp

#pragma once

#include <memory>

namespace KaliLaska {
class MenuImp;

class MenuImpFactory {
public:
  virtual ~MenuImpFactory() = default;

  virtual std::unique_ptr<MenuImp> createMenuImp() = 0;
};
} // namespace KaliLaska
