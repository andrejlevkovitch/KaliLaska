// WindowSdlFactory.cpp

#include "WindowSdlFactory.hpp"
#include "KaliLaska/Window.hpp"
#include "MenuImgui.hpp"
#include "WindowSdl.hpp"
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
  // all implementation will be sdl implementations, because in other way will
  // be other factory
  return std::make_unique<MenuImgui>(
      reinterpret_cast<WindowSdl *>(window.implementation())->window_);
}
} // namespace KaliLaska
