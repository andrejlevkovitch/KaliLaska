// WindowImpFactory.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include "KaliLaska/Size.hpp"
#include "KaliLaska/kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class WindowImp;
class Window;

class KALILASKA_EXPORT WindowImpFactory {
public:
  virtual ~WindowImpFactory() = default;

  /**\param window object, for which create implementation
   * \return if window can not be created - have to return nullptr
   */
  virtual std::unique_ptr<WindowImp> createWindowImp(Window &window) = 0;
  /**\return if window can not be created - have to return nullptr
   */
  virtual std::unique_ptr<WindowImp>
  createWindowImp(Window &window, const char *title, Size size) = 0;
  /**\return if window can not be created - have to return nullptr
   */
  virtual std::unique_ptr<WindowImp> createWindowImp(Window &    window,
                                                     const char *title,
                                                     Point       point,
                                                     Size        size) = 0;

  /**\brief unregister created window. You can set void implementation, if you
   * not store the window-s in you inheritor factory
   */
  virtual void resetWindow(Window *window) = 0;
};
} // namespace KaliLaska
