// WindowSdlFactory.hpp

#pragma once

#include "window/imp/WindowImpFactory.hpp"
#include <list>
#include <map>

namespace KaliLaska {
class WindowSdlFactory final : public WindowImpFactory {
public:
  std::unique_ptr<WindowImp> createWindowImp(Window &window) override;
  std::unique_ptr<WindowImp>
                             createWindowImp(Window &window, std::string_view title, Size size) override;
  std::unique_ptr<WindowImp> createWindowImp(Window &         window,
                                             std::string_view title,
                                             Point            pos,
                                             Size             size) override;

  std::unique_ptr<MenuImp> createMenuImp(Window &window) override;

  /**\return pointer to window from id of SDL_Window
   */
  Window *getWindowFromId(uint32_t id) const;

  /**\brief unstore pointer to input window. If window with input pointer not
   * stored - does nothing
   */
  void resetWindow(Window *window) override;

  std::list<Window *> allWindows();

private:
  std::map<uint32_t, Window *> windows_;
};
} // namespace KaliLaska
