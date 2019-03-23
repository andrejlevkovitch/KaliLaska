// MousePressEvent.cpp

#include "KaliLaska/MousePressEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "imp/EventImpFactory.hpp"
#include "imp/MousePressEventImp.hpp"

namespace KaliLaska {
MousePressEvent::MousePressEvent(Mouse::Button button,
                                 Mouse::Click  click,
                                 Point         pos)
    : Event{Type::MousePressEvent}
    , imp_{Application::eventFactory()->createMousePressEventImp(
          button, click, pos)} {
}

MousePressEvent::MousePressEvent(std::unique_ptr<MousePressEventImp> imp)
    : Event{Type::MousePressEvent}
    , imp_{std::move(imp)} {
}

MousePressEvent::~MousePressEvent() {
}

Mouse::Button MousePressEvent::button() const {
  return imp_->button();
}

Mouse::Buttons MousePressEvent::buttons() const {
  return imp_->buttons();
}

Mouse::Click MousePressEvent::click() const {
  return imp_->click();
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
  stream << ", click " << static_cast<int>(event.click());
  return stream;
}
} // namespace KaliLaska
