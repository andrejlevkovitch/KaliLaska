// WindowImpFactory.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include "KaliLaska/Size.hpp"
#include <memory>

namespace KaliLaska {
class WindowImp;
class Window;
class MenuImp;

class WindowImpFactory {
public:
  virtual ~WindowImpFactory() = default;

  /**\param window object, for which create implementation
   * \throw exceptions from WindowImp at creation time
   */
  virtual std::unique_ptr<WindowImp> createWindowImp(Window &window) = 0;
  /**\throw exceptions from WindowImp at creation time
   */
  virtual std::unique_ptr<WindowImp>
  createWindowImp(Window &window, std::string_view title, Size size) = 0;
  /**\throw exceptions from WindowImp at creation time
   */
  virtual std::unique_ptr<WindowImp> createWindowImp(Window &         window,
                                                     std::string_view title,
                                                     Point            point,
                                                     Size             size) = 0;

  virtual std::unique_ptr<MenuImp> createMenuImp(Window &window) = 0;

  /**\brief unregister created window. You can set void implementation, if you
   * not store the window-s in you inheritor factory
   */
  virtual void resetWindow(Window *window) = 0;
};
} // namespace KaliLaska
