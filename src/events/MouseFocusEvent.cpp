// MouseFocusEvent.cpp

#include "KaliLaska/MouseFocusEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/imp/EventImpFactory.hpp"

namespace KaliLaska {
MouseFocusEvent::MouseFocusEvent(Mouse::Focus focus)
    : Event{Type::MouseFocusEvent}
    , imp_{Application::eventFactory()->createMouseFocusEvent(focus)} {
}

MouseFocusEvent::MouseFocusEvent(std::unique_ptr<MouseFocusEventImp> imp)
    : Event{Type::MouseFocusEvent}
    , imp_{std::move(imp)} {
}

Mouse::Focus MouseFocusEvent::focus() const {
  return imp_->focus();
}

std::ostream &operator<<(std::ostream &stream, const MouseFocusEvent &event) {
  stream << "MouseFocusEvent: focus ";
  switch (event.focus()) {
  case Mouse::Focus::Enter:
    stream << "Enter";
    break;
  case Mouse::Focus::Leave:
    stream << "Leave";
    break;
  default:
    stream << "Invalid";
    break;
  }
  return stream;
}
} // namespace KaliLaska
