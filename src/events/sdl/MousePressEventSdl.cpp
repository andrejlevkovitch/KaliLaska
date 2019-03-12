// MousePressEventSdl.cpp

#include "MousePressEventSdl.hpp"
#include "SdlEvents.hpp"

namespace KaliLaska {
MousePressEventSdl::MousePressEventSdl(Mouse::Button button,
                                       Mouse::Click  click,
                                       Point         clickPos)
    : event_{}
    , buttons_{} {
  event_.button = sdlButton(button);
  event_.x      = clickPos.x();
  event_.y      = clickPos.y();
  event_.clicks = sdlMouseClick(click);
}

MousePressEventSdl::MousePressEventSdl(SDL_MouseButtonEvent sdlEvent,
                                       uint32_t             button)
    : event_{sdlEvent}
    , buttons_{button} {
}

Mouse::Button MousePressEventSdl::button() const {
  return mouseButton(event_.button);
}

Mouse::Buttons MousePressEventSdl::buttons() const {
  return mouseButtons(buttons_);
}

Mouse::Click MousePressEventSdl::click() const {
  return mouseClick(event_.clicks);
}

Point MousePressEventSdl::clickPos() const {
  return Point{event_.x, event_.y};
}
} // namespace KaliLaska
