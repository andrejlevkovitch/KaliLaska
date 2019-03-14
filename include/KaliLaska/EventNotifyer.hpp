// EventNotifyer.hpp

#pragma once

#include "KaliLaska/kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class Window;
class Event;

class KALILASKA_EXPORT EventNotifyer {
public:
  static void notify(Window *, std::unique_ptr<Event> event);
};
} // namespace KaliLaska
