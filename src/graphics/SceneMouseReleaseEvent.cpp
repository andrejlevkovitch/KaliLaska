// SceneMouseReleaseEvent.cpp

#include "KaliLaska/SceneMouseReleaseEvent.hpp"
#include "KaliLaska/MouseReleaseEvent.hpp"

namespace KaliLaska {
SceneMouseReleaseEvent::SceneMouseReleaseEvent(
    std::unique_ptr<MouseReleaseEvent> event)
    : Event{Type::SceneMouseReleaseEvent}
    , event_{std::move(event)} {
}

SceneMouseReleaseEvent::~SceneMouseReleaseEvent() {
}

Mouse::Button SceneMouseReleaseEvent::button() const {
  return event_->button();
}

Mouse::Buttons SceneMouseReleaseEvent::buttons() const {
  return event_->buttons();
}

Point SceneMouseReleaseEvent::clickPos() const {
  // FIXME not implement
  return {};
}

Point SceneMouseReleaseEvent::clickViewPos() const {
  return event_->clickPos();
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &                           stream,
                         const KaliLaska::SceneMouseReleaseEvent &event) {
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
  return stream;
  return stream;
}
