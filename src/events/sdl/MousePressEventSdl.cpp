// MousePressEventSdl.cpp

#include "MousePressEventSdl.hpp"
#include "SdlEvents.hpp"

namespace KaliLaska {
MousePressEventSdl::MousePressEventSdl(Mouse::Button button, Point clickPos)
    : event_{} {
  event_.button = sdlButton(button);
  event_.x      = clickPos.x();
  event_.y      = clickPos.y();
}

MousePressEventSdl::MousePressEventSdl(SDL_MouseButtonEvent sdlEvent)
    : event_{sdlEvent} {
}

Mouse::Button MousePressEventSdl::button() const {
  return mouseButton(event_.button);
}

Mouse::Buttons MousePressEventSdl::buttons() const {
  return mouseButtons(::SDL_GetMouseState(nullptr, nullptr));
}

Point MousePressEventSdl::clickPos() const {
  return Point{event_.x, event_.y};
}
} // namespace KaliLaska
