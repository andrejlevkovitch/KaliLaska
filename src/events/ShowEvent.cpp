// ShowEvent.cpp

#include "KaliLaska/ShowEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "imp/EventImpFactory.hpp"
#include "imp/ShowEventImp.hpp"

namespace KaliLaska {
ShowEvent::ShowEvent(ShowAction action)
    : Event{Type::ShowEvent}
    , imp_{Application::eventFactory()->createShowEventImp(action)} {
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

std::ostream &operator<<(std::ostream &stream, const ShowEvent &event) {
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
} // namespace KaliLaska
