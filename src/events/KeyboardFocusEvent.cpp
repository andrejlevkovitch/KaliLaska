// KeyboardFocusEvent.cpp

#include "KaliLaska/KeyboardFocusEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "application/imp/ApplicationImp.hpp"
#include "events/imp/EventImpFactory.hpp"
#include "events/imp/KeyboardFocusEventImp.hpp"

namespace KaliLaska {
KeyboardFocusEvent::KeyboardFocusEvent(Keyboard::Focus focus)
    : Event{Type::KeyboardFocusEvent}
    , imp_{Application::implementation()
               ->eventImpFactory()
               ->createKeyboardFocusEventImp(focus)} {
}

KeyboardFocusEvent::KeyboardFocusEvent(
    std::unique_ptr<KeyboardFocusEventImp> imp)
    : Event{Type::KeyboardFocusEvent}
    , imp_{std::move(imp)} {
}

KeyboardFocusEvent::~KeyboardFocusEvent() {
}

Keyboard::Focus KeyboardFocusEvent::focus() const {
  return imp_->focus();
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &                       stream,
                         const KaliLaska::KeyboardFocusEvent &event) {
  stream << "KeyboardFocusEvent: focus ";
  switch (event.focus()) {
  case KaliLaska::Keyboard::Focus::Gained:
    stream << "Gained";
    break;
  case KaliLaska::Keyboard::Focus::Lost:
    stream << "Lost";
    break;
  default:
    stream << "Invalid";
    break;
  }
  return stream;
}
