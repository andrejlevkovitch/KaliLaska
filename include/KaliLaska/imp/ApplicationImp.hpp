// ApplicationImp.hpp

#pragma once

namespace KaliLaska {
class WindowImpFactory;
class EventImpFactory;

/**\brief interface for Application
 */
class ApplicationImp {
public:
  virtual ~ApplicationImp() = default;

  /**\brief start main loop
   */
  virtual int exec() = 0;

  /**\brief break main loop
   */
  virtual void exit(int code) = 0;

  virtual WindowImpFactory *windowFactory() const = 0;
  virtual EventImpFactory * eventFactory() const  = 0;

  /**\return current update per second (interval between main cickle iterations)
   */
  virtual int ups() const = 0;

  /**\brief set update per second
   */
  virtual void setUps(int ups) = 0;
};
} // namespace KaliLaska
