// CloseEvent.cpp

#include "KaliLaska/CloseEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/imp/CloseEventImp.hpp"
#include "KaliLaska/imp/EventImpFactory.hpp"
#include "debug.hpp"

namespace KaliLaska {
CloseEvent::CloseEvent()
    : Event{Event::Type::CloseEvent}
    , imp_{Application::eventFactory()->createCloseEventImp()} {
}

CloseEvent::CloseEvent(std::unique_ptr<CloseEventImp> imp)
    : Event{Event::Type::CloseEvent}
    , imp_{std::move(imp)} {
}

std::ostream &operator<<(std::ostream &stream, const CloseEvent &event) {
  UNUSED(event);
  stream << "CloseEvent";
  return stream;
}
} // namespace KaliLaska
