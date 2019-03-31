// AppFactory.hpp

#pragma once

#include "imp/ApplicationImp.hpp"
#include <memory>

namespace KaliLaska {
class AppFactory {
public:
  static std::unique_ptr<ApplicationImp> createAppImp();
};
} // namespace KaliLaska
