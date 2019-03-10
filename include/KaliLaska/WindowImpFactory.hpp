// WindowImpFactory.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include "KaliLaska/Size.hpp"
#include <memory>

namespace KaliLaska {
class WindowImp;
class Window;

class WindowImpFactory {
public:
  virtual ~WindowImpFactory() = default;

  /**\param window object, for which create implementation
   */
  virtual std::unique_ptr<WindowImp> createWindowImp(Window &window) = 0;
  virtual std::unique_ptr<WindowImp>
                                     createWindowImp(Window &window, const char *title, Size size) = 0;
  virtual std::unique_ptr<WindowImp> createWindowImp(Window &    window,
                                                     const char *title,
                                                     Point       point,
                                                     Size        size) = 0;

  virtual void resetWindow(Window *window) = 0;
};
} // namespace KaliLaska
