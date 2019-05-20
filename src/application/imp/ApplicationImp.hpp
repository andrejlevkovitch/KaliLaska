// ApplicationImp.hpp

#pragma once

#include <chrono>

namespace KaliLaska {
class WindowImpFactory;
class EventImpFactory;
class GraphicsSceneImpFactory;

class Object;

/**\brief interface for Application
 */
class ApplicationImp {
public:
  virtual ~ApplicationImp() = default;

  /**\brief start main loop
   * \throw can throw runtime_error if causes internal error
   */
  virtual int exec() = 0;

  /**\brief break main loop
   */
  virtual void exit(int code) = 0;

  /**\return factory, which build implementations for windows
   */
  virtual WindowImpFactory *windowImpFactory() const = 0;
  /**\return factory, which build implementations for events
   */
  virtual EventImpFactory *eventImpFactory() const = 0;
  /**\return factory, which build implementations for graphics scenes
   */
  virtual GraphicsSceneImpFactory *graphicsSceneImpFactory() const = 0;

  /**\brief set interval between call updates for objects
   */
  virtual void setIterationTimeInterval(std::chrono::milliseconds time) = 0;
  /**\return interval between call updates for objects
   */
  virtual std::chrono::milliseconds iterationTimeInterval() const = 0;

  virtual void registerObject(Object *obj)   = 0;
  virtual void unregisterObject(Object *obj) = 0;
};
} // namespace KaliLaska
