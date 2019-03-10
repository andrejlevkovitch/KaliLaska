// EventNotifyer.hpp

#pragma once

#include <memory>

namespace KaliLaska {
class Window;
class Event;

class EventNotifyer {
public:
  static void notify(Window *, std::unique_ptr<Event> event);
};
} // namespace KaliLaska
