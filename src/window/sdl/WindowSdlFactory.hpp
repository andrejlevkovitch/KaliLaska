// WindowSdlFactory.hpp

#pragma once

#include "window/imp/WindowImpFactory.hpp"
#include <list>
#include <map>

namespace KaliLaska {
class WindowSdlFactory final : public WindowImpFactory {
public:
  std::unique_ptr<WindowImp> createWindowImp(AbstractWindow &window) override;
  std::unique_ptr<WindowImp> createWindowImp(AbstractWindow & window,
                                             std::string_view title,
                                             Size             size) override;
  std::unique_ptr<WindowImp> createWindowImp(AbstractWindow & window,
                                             std::string_view title,
                                             Point            pos,
                                             Size             size) override;

  std::unique_ptr<MenuImp> createMenuImp(AbstractWindow &window) override;

  /**\return pointer to window from id of SDL_Window.
   *
   * \warning If id is is of SDL_Window, which was be destroyed, then you get
   * invalid pointer. So you have to use this method only with valid id. PS: we
   * not remove destroyed windows from map, because the map only for concrete
   * factory (abstract factory do not know nothing about this), and we not use
   * many windows in our programs. So, IMHO, we not need remove this.
   */
  AbstractWindow *getWindowFromId(uint32_t id) const;

private:
  std::map<uint32_t, AbstractWindow *> windows_;
};
} // namespace KaliLaska
