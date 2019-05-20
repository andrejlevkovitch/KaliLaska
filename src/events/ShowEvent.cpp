// ShowEvent.cpp

#include "KaliLaska/ShowEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "application/imp/ApplicationImp.hpp"
#include "events/imp/EventImpFactory.hpp"
#include "events/imp/ShowEventImp.hpp"

namespace KaliLaska {
ShowEvent::ShowEvent(ShowAction action)
    : Event{Type::ShowEvent}
    , imp_{Application::implementation()->eventImpFactory()->createShowEventImp(
          action)} {
}

ShowEvent::ShowEvent(std::unique_ptr<ShowEventImp> imp)
    : Event{Type::ShowEvent}
    , imp_{std::move(imp)} {
}

ShowEvent::~ShowEvent() {
}

ShowAction ShowEvent::action() const {
  return imp_->action();
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &              stream,
                         const KaliLaska::ShowEvent &event) {
  using namespace KaliLaska;
  stream << "ShowEvent: action ";
  switch (event.action()) {
  case ShowAction::Shown:
    stream << "Shown";
    break;
  case ShowAction::Hidden:
    stream << "Hidden";
    break;
  default:
    stream << "Invalid";
    break;
  }
  return stream;
}
