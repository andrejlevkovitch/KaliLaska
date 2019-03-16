// KeyboardFocusEvent.cpp

#include "KaliLaska/KeyboardFocusEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/imp/EventImpFactory.hpp"

namespace KaliLaska {
KeyboardFocusEvent::KeyboardFocusEvent(Keyboard::Focus focus)
    : Event{Type::KeyboardFocusEvent}
    , imp_{Application::eventFactory()->createKeyboardFocusEventImp(focus)} {
}

KeyboardFocusEvent::KeyboardFocusEvent(
    std::unique_ptr<KeyboardFocusEventImp> imp)
    : Event{Type::KeyboardFocusEvent}
    , imp_{std::move(imp)} {
}

Keyboard::Focus KeyboardFocusEvent::focus() const {
  return imp_->focus();
}

std::ostream &operator<<(std::ostream &            stream,
                         const KeyboardFocusEvent &event) {
  stream << "KeyboardFocusEvent: focus ";
  switch (event.focus()) {
  case Keyboard::Focus::Gained:
    stream << "Gained";
    break;
  case Keyboard::Focus::Lost:
    stream << "Lost";
    break;
  default:
    stream << "Invalid";
    break;
  }
  return stream;
}
} // namespace KaliLaska
