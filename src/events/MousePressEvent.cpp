// MousePressEvent.cpp

#include "KaliLaska/MousePressEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/EventImpFactory.hpp"
#include "KaliLaska/MousePressEventImp.hpp"

namespace KaliLaska {
MousePressEvent::MousePressEvent(Mouse::Button button, Point pos)
    : Event{Type::MouseMoveEvent}
    , imp_{Application::eventFactory()->createMousePressImp(button, pos)} {
}

MousePressEvent::MousePressEvent(std::unique_ptr<MousePressEventImp> imp)
    : Event{Type::MousePressEvent}
    , imp_{std::move(imp)} {
}

Mouse::Button MousePressEvent::button() const {
  if (imp_) {
    return imp_->button();
  }
  return {};
}

Mouse::Buttons MousePressEvent::buttons() const {
  if (imp_) {
    imp_->buttons();
  }
  return {};
}

Point MousePressEvent::clickPos() const {
  if (imp_) {
    return imp_->clickPos();
  }
  return {};
}

std::ostream &operator<<(std::ostream &stream, const MousePressEvent &event) {
  stream << "MousePressEvent: clickPos " << event.clickPos() << ", button ";
  switch (event.button()) {
  case Mouse::Button::Left:
    stream << "Left";
    break;
  case Mouse::Button::Right:
    stream << "Right";
    break;
  case Mouse::Button::Middle:
    stream << "Middle";
    break;
  default:
    stream << "Unknow";
    break;
  }
  return stream;
}
} // namespace KaliLaska
