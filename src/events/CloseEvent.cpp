// CloseEvent.cpp

#include "KaliLaska/CloseEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "application/imp/ApplicationImp.hpp"
#include "debug.hpp"
#include "events/imp/CloseEventImp.hpp"
#include "events/imp/EventImpFactory.hpp"

namespace KaliLaska {
CloseEvent::CloseEvent()
    : Event{Event::Type::CloseEvent}
    , imp_{Application::implementation()
               ->eventImpFactory()
               ->createCloseEventImp()} {
}

CloseEvent::CloseEvent(std::unique_ptr<CloseEventImp> imp)
    : Event{Event::Type::CloseEvent}
    , imp_{std::move(imp)} {
}

CloseEvent::~CloseEvent() {
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &               stream,
                         const KaliLaska::CloseEvent &event) {
  UNUSED(event);
  stream << "CloseEvent";
  return stream;
}
