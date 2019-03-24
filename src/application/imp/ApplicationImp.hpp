// ApplicationImp.hpp

#pragma once

#include <chrono>

namespace KaliLaska {
class WindowImpFactory;
class EventImpFactory;
class GraphicsSceneImpFactory;

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

  virtual WindowImpFactory *windowFactory() const = 0;
  virtual EventImpFactory * eventFactory() const  = 0;

  virtual void setIterationTimeInterval(std::chrono::milliseconds time) = 0;

  virtual std::chrono::milliseconds iterationTimeInterval() const = 0;

  virtual GraphicsSceneImpFactory *sceneFactory() = 0;
};
} // namespace KaliLaska
