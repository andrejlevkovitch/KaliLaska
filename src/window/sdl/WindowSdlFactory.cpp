// WindowSdlFactory.cpp

#include "WindowSdlFactory.hpp"
#include "KaliLaska/AbstractWindow.hpp"
#include "MenuSdl.hpp"
#include "WindowSdl.hpp"
#include <SDL2/SDL.h>
#include <algorithm>

namespace KaliLaska {
std::unique_ptr<WindowImp>
WindowSdlFactory::createWindowImp(AbstractWindow &window) {
  try {
    auto retval = std::make_unique<WindowSdl>();
    windows_.emplace(retval->id(), &window);
    return retval;
  } catch (const std::runtime_error &) {
    throw;
  }
}

std::unique_ptr<WindowImp> WindowSdlFactory::createWindowImp(
    AbstractWindow &window, std::string_view title, Size size) {
  try {
    auto retval = std::make_unique<WindowSdl>(title, size);
    windows_.emplace(retval->id(), &window);
    return retval;
  } catch (const std::runtime_error &) {
    throw;
  }
}

std::unique_ptr<WindowImp> WindowSdlFactory::createWindowImp(
    AbstractWindow &window, std::string_view title, Point pos, Size size) {
  try {
    auto retval = std::make_unique<WindowSdl>(title, pos, size);
    windows_.emplace(retval->id(), &window);
    return retval;
  } catch (const std::runtime_error &) {
    throw;
  }
}

AbstractWindow *WindowSdlFactory::getWindowFromId(uint32_t id) const {
  if (auto found = windows_.find(id); found != windows_.end()) {
    return found->second;
  }
  return nullptr;
}

std::unique_ptr<MenuImp>
WindowSdlFactory::createMenuImp(AbstractWindow &window) {
  if (auto iter = std::find_if(windows_.begin(),
                               windows_.end(),
                               [winPtr = &window](const auto &val) {
                                 if (val.second == winPtr) {
                                   return true;
                                 }
                                 return false;
                               });
      iter != windows_.end()) {
    return std::make_unique<MenuSdl>(::SDL_GetWindowFromID(iter->first));
  }
  return {};
}
} // namespace KaliLaska
