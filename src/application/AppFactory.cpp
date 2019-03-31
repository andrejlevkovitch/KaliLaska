// AppFactory.cpp

#include "AppFactory.hpp"
#include "sdl/ApplicationSdl.hpp"

namespace KaliLaska {
std::unique_ptr<ApplicationImp> AppFactory::createAppImp() {
  return std::make_unique<ApplicationSdl>();
}
} // namespace KaliLaska
