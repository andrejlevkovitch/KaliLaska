// WindowImp.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include "KaliLaska/Size.hpp"

namespace KaliLaska {
class CloseEvent;

/**\brief abstract base class which provides interface for winodw
 */
class WindowImp {
public:
  virtual ~WindowImp() = default;

  virtual Point pos() const       = 0;
  virtual void  setPos(Point pos) = 0;

  virtual Size size() const = 0;

  virtual Size drawSize() const = 0;

  virtual void setSize(Size size) = 0;

  virtual const char *title() const = 0;

  virtual void setTitle(const char *title) = 0;

  virtual bool isValid() const = 0;

  virtual bool isHide() const = 0;

  virtual void hide()  = 0;
  virtual void show()  = 0;
  virtual void raise() = 0;

  virtual void setFullScr() = 0;

  virtual void minimize() = 0;
  virtual void maximize() = 0;
  virtual void restore()  = 0;

private:
};
} // namespace KaliLaska
