// MouseMoveEvent.cpp

#include "KaliLaska/MouseMoveEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "imp/EventImpFactory.hpp"
#include "imp/MouseMoveEventImp.hpp"

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

MouseMoveEvent::~MouseMoveEvent() {
}

Mouse::Buttons MouseMoveEvent::buttons() const {
  return imp_->buttons();
}

Point MouseMoveEvent::currentPos() const {
  return imp_->currentPos();
}

Point MouseMoveEvent::previousPos() const {
  return imp_->previousPos();
}

Point MouseMoveEvent::distance() const {
  return imp_->distance();
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &                   stream,
                         const KaliLaska::MouseMoveEvent &event) {
  stream << "MouseMoveEvent: curPos " << event.currentPos() << ", prevPos "
         << event.previousPos();
  if (auto buttons = event.buttons()) {
    stream << ", buttons";
    stream << ((buttons & KaliLaska::Mouse::Button::Left) ? " Left" : "");
    stream << ((buttons & KaliLaska::Mouse::Button::Right) ? " Right" : "");
    stream << ((buttons & KaliLaska::Mouse::Button::Middle) ? " Middle" : "");
  }
  return stream;
}
