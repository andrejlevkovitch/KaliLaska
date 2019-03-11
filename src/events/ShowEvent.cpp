// ShowEvent.cpp

#include "KaliLaska/ShowEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/imp/EventImpFactory.hpp"

namespace KaliLaska {
ShowEvent::ShowEvent(ShowAction action)
    : Event{Type::ShowEvent}
    , imp_{Application::eventFactory()->createShowEventImp(action)} {
}

ShowEvent::ShowEvent(std::unique_ptr<ShowEventImp> imp)
    : Event{Type::ShowEvent}
    , imp_{std::move(imp)} {
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
    // case ShowAction::Maximized:
    //  stream << "Maximized";
    //  break;
    // case ShowAction::Minimized:
    //  stream << "Minimized";
    //  break;
    // case ShowAction::Restored:
    //  stream << "Restored";
    //  break;
  default:
    stream << "Invalid";
    break;
  }
  return stream;
}
} // namespace KaliLaska
