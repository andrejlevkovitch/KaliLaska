// WindowImp.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include "KaliLaska/Size.hpp"

namespace KaliLaska {
class CloseEvent;
class Color;

/**\brief abstract base class which provides interface for winodw.
 * \throws constructors of inheritor can throw runtime_error if window can not
 * be created
 */
class WindowImp {
public:
  virtual ~WindowImp() = default;

  /**\return top-left corner of the window
   */
  virtual Point pos() const       = 0;
  virtual void  setPos(Point pos) = 0;

  /**\return complete size of window (with borders)
   */
  virtual Size size() const       = 0;
  virtual void setSize(Size size) = 0;

  /**\return size of drawable area of window
   */
  virtual Size drawSize() const = 0;

  virtual std::string_view title() const = 0;

  virtual void setTitle(std::string_view title) = 0;

  /**\return true if window is currently hidden, false - other wise
   */
  virtual bool isHide() const = 0;

  virtual void hide() = 0;
  virtual void show() = 0;

  virtual void setFullScr()      = 0;
  virtual bool isFullScr() const = 0;

  virtual void setResizable(bool value) = 0;
  virtual bool isResizable() const      = 0;

  virtual void swapWindow() const = 0;

  virtual void makeCurrent() const = 0;
};
} // namespace KaliLaska
