// MouseFocusEvent.cpp

#include "KaliLaska/MouseFocusEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "application/imp/ApplicationImp.hpp"
#include "events/imp/EventImpFactory.hpp"
#include "events/imp/MouseFocusEventImp.hpp"

namespace KaliLaska {
MouseFocusEvent::MouseFocusEvent(Mouse::Focus focus)
    : Event{Type::MouseFocusEvent}
    , imp_{Application::implementation()
               ->eventImpFactory()
               ->createMouseFocusEventImp(focus)} {
}

MouseFocusEvent::MouseFocusEvent(std::unique_ptr<MouseFocusEventImp> imp)
    : Event{Type::MouseFocusEvent}
    , imp_{std::move(imp)} {
}

MouseFocusEvent::~MouseFocusEvent() {
}

Mouse::Focus MouseFocusEvent::focus() const {
  return imp_->focus();
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &                    stream,
                         const KaliLaska::MouseFocusEvent &event) {
  stream << "MouseFocusEvent: focus ";
  switch (event.focus()) {
  case KaliLaska::Mouse::Focus::Enter:
    stream << "Enter";
    break;
  case KaliLaska::Mouse::Focus::Leave:
    stream << "Leave";
    break;
  default:
    stream << "Invalid";
    break;
  }
  return stream;
}
