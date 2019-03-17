// Window.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include "KaliLaska/Size.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class WindowImp;
class EventNotifyer;

class Event;

class CloseEvent;
class ShowEvent;
class ResizeEvent;
class MoveEvent;

class MouseFocusEvent;
class MousePressEvent;
class MouseMoveEvent;
class MouseReleaseEvent;
class MouseWheelEvent;

class KeyboardFocusEvent;
class KeyPressEvent;
class KeyReleaseEvent;

/**\warning if you close last window Application break the cikle and program
 * finish
 */
class KALILASKA_EXPORT Window {
  friend EventNotifyer;

public:
  /**\brief create window with minimal size in corner of screen
   * \throw std::runtime_error if window can not be crated
   */
  Window();
  /**\brief create centered window
   * \throw std::runtime_error if window can not be crated
   */
  Window(const char *title, Size size);

  /**\throw std::runtime_error if window can not be crated
   */
  Window(const char *title, Point pos, Size size);
  virtual ~Window();

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  Point pos() const;
  void  setPos(Point pos);

  /**\return size of window in screen coordinates
   */
  Size size() const;

  /**\return drawable size of window
   */
  Size drawSize() const;

  void setSize(Size size);

  /**\return title of window. If title not set return void string
   */
  const char *title() const;

  void setTitle(const char *title);

  /**\return true if window is hidden of if window is invalid
   */
  bool isHide() const;

  void hide();
  void show();

  void setFullScr();
  bool isFullScr() const;

  /**\brief change resize state of window. By default window is not resizable
   * \warning you can not chang resizable state of fullscreen window
   */
  void setResizable(bool value);
  bool isResizable() const;

  /**\brief generate close event for current window
   */
  void close();

protected:
  /**\warning after call this method you can not call the object
   * \brief call before window will be closed. If you reimplemend this method
   * you have to call Window::closeEvent, other way window will not be closed!
   */
  virtual void closeEvent(std::unique_ptr<CloseEvent> event);
  /**\brief By default does nothing
   */
  virtual void showEvent(std::unique_ptr<ShowEvent> event);
  /**\brief By default does nothing
   */
  virtual void resizeEvent(std::unique_ptr<ResizeEvent> event);
  /**\brief By default does nothing
   */
  virtual void moveEvent(std::unique_ptr<MoveEvent> event);

  /**\brief call when mouse leave or enter in area of the window. By default
   * does nothing
   */
  virtual void mouseFocusEvent(std::unique_ptr<MouseFocusEvent> event);
  /**\brief By default does nothing
   * \warning if case double click you can get two mouse press event (this
   * dependence from implementation) with single click and second - double
   * click. Be carefull
   */
  virtual void mousePressEvent(std::unique_ptr<MousePressEvent> event);
  /**\brief By default does nothing
   */
  virtual void mouseReleaseEvent(std::unique_ptr<MouseReleaseEvent> event);
  /**\brief By default does nothing
   */
  virtual void mouseMoveEvent(std::unique_ptr<MouseMoveEvent> event);
  /**\brief By default does nothing
   */
  virtual void mouseWheelEvent(std::unique_ptr<MouseWheelEvent> event);

  /**\brief By default does nothing
   */
  virtual void keyboardFocusEvent(std::unique_ptr<KeyboardFocusEvent> event);
  /**\brief By default does nothing
   */
  virtual void keyPressEvent(std::unique_ptr<KeyPressEvent> event);
  /**\brief By default does nothing
   */
  virtual void keyReleaseEvent(std::unique_ptr<KeyReleaseEvent> event);

  /**\brief if you implement you'r own type of events you can notify window from
   * Application by the method. By default does nothing
   */
  virtual void userEvent(std::unique_ptr<Event> event);

private:
  std::unique_ptr<WindowImp> imp_;
};
} // namespace KaliLaska
