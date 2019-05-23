// EventNotifyer.hpp

#pragma once

#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class AbstractWindow;
class Event;

/**\brief main function of the class - call protected members of Window
 */
class EventNotifyer {
public:
  static void notify(AbstractWindow *window, std::unique_ptr<Event> event);
};
} // namespace KaliLaska
