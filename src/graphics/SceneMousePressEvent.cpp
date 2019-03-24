// SceneMousePressEvent.cpp

#include "KaliLaska/SceneMousePressEvent.hpp"
#include "KaliLaska/MousePressEvent.hpp"

namespace KaliLaska {
SceneMousePressEvent::SceneMousePressEvent(
    std::unique_ptr<MousePressEvent> event)
    : Event{Type::SceneMousePressEvent}
    , event_{std::move(event)} {
}

SceneMousePressEvent::~SceneMousePressEvent() {
}

Mouse::Button SceneMousePressEvent::button() const {
  return event_->button();

  Point p{10, 10};
}

Mouse::Buttons SceneMousePressEvent::buttons() const {
  return event_->buttons();
}

Mouse::Click SceneMousePressEvent::click() const {
  return event_->click();
}

Point SceneMousePressEvent::clickPos() const {
  // FIXME not implement
  return {};
}

Point SceneMousePressEvent::clickViewPos() const {
  return event_->clickPos();
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &                         stream,
                         const KaliLaska::SceneMousePressEvent &event) {
  using namespace KaliLaska;
  stream << "SceneMousePressEvent: clickPos " << event.clickPos()
         << ", viewClickPos " << event.clickViewPos() << ", button ";
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
