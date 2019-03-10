// MouseWheelEvent.cpp

#include "KaliLaska/MouseWheelEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/EventImpFactory.hpp"
#include "KaliLaska/MouseWheelEventImp.hpp"

namespace KaliLaska {
MouseWheelEvent::MouseWheelEvent(Mouse::Scale scale)
    : Event{Type::MouseWheelEvent}
    , imp_{Application::eventFactory()->createMouseWheelEventImp(scale)} {
}

MouseWheelEvent::MouseWheelEvent(std::unique_ptr<MouseWheelEventImp> imp)
    : Event{Type::MouseWheelEvent}
    , imp_{std::move(imp)} {
}

Point MouseWheelEvent::position() const {
  if (imp_) {
    return imp_->position();
  }
  return {};
}

Mouse::Scale MouseWheelEvent::scale() const {
  if (imp_) {
    return imp_->scale();
  }
  return {};
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
