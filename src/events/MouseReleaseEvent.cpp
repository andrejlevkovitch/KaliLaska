// MouseReleaseEvent.cpp

#include "KaliLaska/MouseReleaseEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/EventImpFactory.hpp"
#include "KaliLaska/MouseReleaseEventImp.hpp"

namespace KaliLaska {
MouseReleaseEvent::MouseReleaseEvent(Mouse::Button button, Point clickPos)
    : Event{Type::MouseReleaseEvent}
    , imp_{Application::eventFactory()->createMouseReleaseImp(button,
                                                              clickPos)} {
}

MouseReleaseEvent::MouseReleaseEvent(std::unique_ptr<MouseReleaseEventImp> imp)
    : Event{Type::MouseReleaseEvent}
    , imp_{std::move(imp)} {
}

Mouse::Button MouseReleaseEvent::button() const {
  if (imp_) {
    return imp_->button();
  }
  return {};
}

Mouse::Buttons MouseReleaseEvent::buttons() const {
  if (imp_) {
    return imp_->buttons();
  }
  return {};
}

Point MouseReleaseEvent::clickPos() const {
  if (imp_) {
    return imp_->clickPos();
  }
  return {};
}

std::ostream &operator<<(std::ostream &stream, const MouseReleaseEvent &event) {
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
