// MousePressEvent.cpp

#include "KaliLaska/MousePressEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/imp/EventImpFactory.hpp"
#include "KaliLaska/imp/MousePressEventImp.hpp"

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
  return imp_->button();
}

Mouse::Buttons MousePressEvent::buttons() const {
  return imp_->buttons();
}

Point MousePressEvent::clickPos() const {
  return imp_->clickPos();
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
