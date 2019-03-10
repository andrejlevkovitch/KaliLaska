// Window.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include "KaliLaska/Size.hpp"
#include <memory>

namespace KaliLaska {
class WindowImp;
class EventNotifyer;

class CloseEvent;
class MousePressEvent;
class MouseMoveEvent;
class MouseReleaseEvent;
class MouseWheelEvent;

class Window {
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

  const char *title() const;

  void setTitle(const char *title);

  /**\return true if window is hidden of if window is invalid
   */
  bool isHide() const;

  void hide();
  void show();
  /**\brief raise this window above others and have focus
   */
  void raise();

  void setFullScr();

  void minimize();
  void maximize();
  /**\brief use this method for restore window after minimize of maximize
   */
  void restore();

  /**\brief generate close event for current window
   */
  void close();

protected:
  /**\warning after call this method you can not call the object
   */
  virtual void closeEvent(std::unique_ptr<CloseEvent> event);
  /**\brief by default does nothing
   */
  virtual void mouseMoveEvent(std::unique_ptr<MouseMoveEvent> event);
  /**\brief by default does nothing
   */
  virtual void mousePressEvent(std::unique_ptr<MousePressEvent> event);
  /**\brief by default does nothing
   */
  virtual void mouseReleaseEvent(std::unique_ptr<MouseReleaseEvent> event);
  /**\brief by default does nothing
   */
  virtual void mouseWheelEvent(std::unique_ptr<MouseWheelEvent> event);

private:
  std::unique_ptr<WindowImp> imp_;
};
} // namespace KaliLaska
