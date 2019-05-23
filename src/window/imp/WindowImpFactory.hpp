// WindowImpFactory.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include "KaliLaska/Size.hpp"
#include <memory>

namespace KaliLaska {
class WindowImp;
class AbstractWindow;
class MenuImp;

class WindowImpFactory {
public:
  virtual ~WindowImpFactory() = default;

  /**\param window object, for which create implementation. We have to set it,
   * because we need get events for the Window, but events generates only for
   * implementation
   *
   * \throw exceptions from WindowImp at creation time
   */
  virtual std::unique_ptr<WindowImp>
  createWindowImp(AbstractWindow &window) = 0;
  /**\throw exceptions from WindowImp at creation time
   */
  virtual std::unique_ptr<WindowImp> createWindowImp(AbstractWindow & window,
                                                     std::string_view title,
                                                     Size             size) = 0;
  /**\throw exceptions from WindowImp at creation time
   */
  virtual std::unique_ptr<WindowImp> createWindowImp(AbstractWindow & window,
                                                     std::string_view title,
                                                     Point            point,
                                                     Size             size) = 0;

  virtual std::unique_ptr<MenuImp> createMenuImp(AbstractWindow &window) = 0;
};
} // namespace KaliLaska
