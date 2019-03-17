// ApplicationImp.hpp

#pragma once

#include "kalilaska_export.h"

namespace KaliLaska {
class WindowImpFactory;
class EventImpFactory;

/**\brief interface for Application
 */
class KALILASKA_EXPORT ApplicationImp {
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

  /**\brief handle quieue of events
   */
  virtual void processEvents() = 0;
};
} // namespace KaliLaska
