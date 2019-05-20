// WindowSdlFactory.cpp

#include "WindowSdlFactory.hpp"
#include "KaliLaska/Window.hpp"
#include "MenuImgui.hpp"
#include "WindowSdl.hpp"
#include <SDL2/SDL.h>
#include <algorithm>

namespace KaliLaska {
std::unique_ptr<WindowImp> WindowSdlFactory::createWindowImp(Window &window) {
  try {
    auto retval = std::make_unique<WindowSdl>();
    windows_.emplace(retval->id(), &window);
    return retval;
  } catch (const std::runtime_error &) {
    throw;
  }
}

std::unique_ptr<WindowImp> WindowSdlFactory::createWindowImp(
    Window &window, std::string_view title, Size size) {
  try {
    auto retval = std::make_unique<WindowSdl>(title, size);
    windows_.emplace(retval->id(), &window);
    return retval;
  } catch (const std::runtime_error &) {
    throw;
  }
}

std::unique_ptr<WindowImp> WindowSdlFactory::createWindowImp(
    Window &window, std::string_view title, Point pos, Size size) {
  try {
    auto retval = std::make_unique<WindowSdl>(title, pos, size);
    windows_.emplace(retval->id(), &window);
    return retval;
  } catch (const std::runtime_error &) {
    throw;
  }
}

Window *WindowSdlFactory::getWindowFromId(uint32_t id) const {
  if (auto found = windows_.find(id); found != windows_.end()) {
    return found->second;
  }
  return nullptr;
}

std::unique_ptr<MenuImp> WindowSdlFactory::createMenuImp(Window &window) {
  if (auto iter = std::find_if(windows_.begin(),
                               windows_.end(),
                               [winPtr = &window](const auto &val) {
                                 if (val.second == winPtr) {
                                   return true;
                                 }
                                 return false;
                               });
      iter != windows_.end()) {
    return std::make_unique<MenuImgui>(::SDL_GetWindowFromID(iter->first));
  }
  return {};
}
} // namespace KaliLaska
