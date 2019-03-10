// WindowSdlFactory.hpp

#pragma once

#include "KaliLaska/WindowImpFactory.hpp"
#include <map>

namespace KaliLaska {
class WindowSdlFactory final : public WindowImpFactory {
public:
  std::unique_ptr<WindowImp> createWindowImp(Window &window) override;
  std::unique_ptr<WindowImp>
                             createWindowImp(Window &window, const char *title, Size size) override;
  std::unique_ptr<WindowImp> createWindowImp(Window &    window,
                                             const char *title,
                                             Point       pos,
                                             Size        size) override;

  Window *getWindowFromId(uint32_t id) const;

  void resetWindow(Window *window) override;

private:
  std::map<uint32_t, Window *> windows_;
};
} // namespace KaliLaska
