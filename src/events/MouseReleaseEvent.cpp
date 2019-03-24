// MouseReleaseEvent.cpp

#include "KaliLaska/MouseReleaseEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "imp/EventImpFactory.hpp"
#include "imp/MouseReleaseEventImp.hpp"

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

MouseReleaseEvent::~MouseReleaseEvent() {
}

Mouse::Button MouseReleaseEvent::button() const {
  return imp_->button();
}

Mouse::Buttons MouseReleaseEvent::buttons() const {
  return imp_->buttons();
}

Point MouseReleaseEvent::clickPos() const {
  return imp_->clickPos();
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &                      stream,
                         const KaliLaska::MouseReleaseEvent &event) {
  using namespace KaliLaska;
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
