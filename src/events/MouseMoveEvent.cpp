// MouseMoveEvent.cpp

#include "KaliLaska/MouseMoveEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/EventImpFactory.hpp"
#include "KaliLaska/MouseMoveEventImp.hpp"

namespace KaliLaska {
MouseMoveEvent::MouseMoveEvent(Mouse::Buttons buttons,
                               Point          curPos,
                               Point          prevPos)
    : Event{Type::MouseMoveEvent}
    , imp_{Application::eventFactory()->createMouseMoveEventImp(
          buttons, curPos, prevPos)} {
}

MouseMoveEvent::MouseMoveEvent(std::unique_ptr<MouseMoveEventImp> imp)
    : Event{Type::MouseMoveEvent}
    , imp_{std::move(imp)} {
}

Mouse::Buttons MouseMoveEvent::buttons() const {
  if (imp_) {
    return imp_->buttons();
  }
  return {};
}

Point MouseMoveEvent::currentPos() const {
  if (imp_) {
    return imp_->currentPos();
  }
  return {};
}

Point MouseMoveEvent::previousPos() const {
  if (imp_) {
    return imp_->previousPos();
  }
  return {};
}

std::ostream &operator<<(std::ostream &stream, const MouseMoveEvent &event) {
  stream << "MouseMoveEvent: curPos " << event.currentPos()
         << ", prevPos: " << event.previousPos();
  if (auto buttons = event.buttons()) {
    stream << "buttons";
    stream << ((buttons & Mouse::Button::Left) ? " Left" : "");
    stream << ((buttons & Mouse::Button::Right) ? " Right" : "");
    stream << ((buttons & Mouse::Button::Middle) ? " Middle" : "");
  }
  return stream;
}
} // namespace KaliLaska
