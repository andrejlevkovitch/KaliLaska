// WindowSdlFactory.cpp

#include "WindowSdlFactory.hpp"
#include "WindowSdl.hpp"
#include <algorithm>

namespace KaliLaska {
std::unique_ptr<WindowImp> WindowSdlFactory::createWindowImp(Window &window) {
  try {
    auto retval = std::make_unique<WindowSdl>();
    auto id     = retval->id();
    windows_.insert(std::pair{id, &window});
    return retval;
  } catch (const std::runtime_error &) {
    throw;
  }
}

std::unique_ptr<WindowImp> WindowSdlFactory::createWindowImp(
    Window &window, std::string_view title, Size size) {
  try {
    auto retval = std::make_unique<WindowSdl>(title, size);
    auto id     = retval->id();
    windows_.insert(std::pair{id, &window});
    return retval;
  } catch (const std::runtime_error &) {
    throw;
  }
}

std::unique_ptr<WindowImp> WindowSdlFactory::createWindowImp(
    Window &window, std::string_view title, Point pos, Size size) {
  try {
    auto retval = std::make_unique<WindowSdl>(title, pos, size);
    auto id     = retval->id();
    windows_.insert(std::pair{id, &window});
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

void WindowSdlFactory::resetWindow(Window *window) {
  // here we can not use getWindowFromId or somthing else, because SDL_Window
  // already not exists
  auto found = std::find_if(windows_.begin(),
                            windows_.end(),
                            [window](const std::pair<uint32_t, Window *> &val) {
                              if (val.second == window) {
                                return true;
                              }
                              return false;
                            });

  if (found != windows_.end()) {
    windows_.erase(found);
  }
}

std::list<Window *> WindowSdlFactory::allWindows() {
  std::list<Window *> retval;
  std::transform(
      windows_.begin(),
      windows_.end(),
      std::back_inserter(retval),
      [](std::pair<uint32_t, Window *> element) { return element.second; });
  return retval;
}
} // namespace KaliLaska
