// SceneMouseMoveEvent.cpp

#include "KaliLaska/SceneMouseMoveEvent.hpp"
#include "KaliLaska/MouseMoveEvent.hpp"

namespace KaliLaska {
SceneMouseMoveEvent::SceneMouseMoveEvent(std::unique_ptr<MouseMoveEvent> event)
    : Event{Event::Type::SceneMouseMoveEvent}
    , event_{std::move(event)} {
}

SceneMouseMoveEvent::~SceneMouseMoveEvent() {
}

Mouse::Buttons SceneMouseMoveEvent::buttons() const {
  return event_->buttons();
}

Point SceneMouseMoveEvent::currentViewPos() const {
  return event_->currentPos();
}

Point SceneMouseMoveEvent::previousViewPos() const {
  return event_->previousPos();
}

Point SceneMouseMoveEvent::currentPos() const {
  // FIXME not implement
  return {};
}

Point SceneMouseMoveEvent::previousPos() const {
  // FIXME not implement
  return {};
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &                        stream,
                         const KaliLaska::SceneMouseMoveEvent &event) {
  using namespace KaliLaska;
  stream << "SceneMouseMoveEvent: curPos " << event.currentPos() << ", prevPos "
         << event.previousPos() << ", curViewPos " << event.currentViewPos()
         << ", prevViewPos " << event.previousViewPos();
  if (auto buttons = event.buttons()) {
    stream << ", buttons";
    stream << ((buttons & Mouse::Button::Left) ? " Left" : "");
    stream << ((buttons & Mouse::Button::Right) ? " Right" : "");
    stream << ((buttons & Mouse::Button::Middle) ? " Middle" : "");
  }
  return stream;
}
