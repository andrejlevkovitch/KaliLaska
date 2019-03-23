// MouseWheelEvent.cpp

#include "KaliLaska/MouseWheelEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "imp/EventImpFactory.hpp"
#include "imp/MouseWheelEventImp.hpp"

namespace KaliLaska {
MouseWheelEvent::MouseWheelEvent(Mouse::Scale scale)
    : Event{Type::MouseWheelEvent}
    , imp_{Application::eventFactory()->createMouseWheelEventImp(scale)} {
}

MouseWheelEvent::MouseWheelEvent(std::unique_ptr<MouseWheelEventImp> imp)
    : Event{Type::MouseWheelEvent}
    , imp_{std::move(imp)} {
}

MouseWheelEvent::~MouseWheelEvent() {
}

Point MouseWheelEvent::position() const {
  return imp_->position();
}

Mouse::Scale MouseWheelEvent::scale() const {
  return imp_->scale();
}

std::ostream &operator<<(std::ostream &stream, const MouseWheelEvent &event) {
  stream << "MouseWheelEvent: position " << event.position() << ", scale ";
  if (event.scale() != Mouse::Scale::Invalid) {
    stream << ((event.scale() == Mouse::Scale::ScaleDown) ? "Down" : "Up");
  } else {
    stream << "Invalid";
  }
  return stream;
}
} // namespace KaliLaska
