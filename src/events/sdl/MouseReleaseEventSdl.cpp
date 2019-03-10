// MouseReleaseEventSdl.cpp

#include "MouseReleaseEventSdl.hpp"
#include "SdlEvents.hpp"

namespace KaliLaska {
MouseReleaseEventSdl::MouseReleaseEventSdl(Mouse::Button button, Point clickPos)
    : event_{} {
  event_.button = sdlButton(button);
  event_.x      = clickPos.x();
  event_.y      = clickPos.y();
}

MouseReleaseEventSdl::MouseReleaseEventSdl(SDL_MouseButtonEvent event)
    : event_{event} {
}

Mouse::Button MouseReleaseEventSdl::button() const {
  switch (event_.button) {
  case SDL_BUTTON_LEFT:
    return Mouse::Button::Left;
  case SDL_BUTTON_RIGHT:
    return Mouse::Button::Right;
  case SDL_BUTTON_MIDDLE:
    return Mouse::Button::Middle;
  default:
    return Mouse::Button::Invalid;
  }
}

Mouse::Buttons MouseReleaseEventSdl::buttons() const {
  return mouseButtons(::SDL_GetMouseState(nullptr, nullptr));
}

Point MouseReleaseEventSdl::clickPos() const {
  return Point{event_.x, event_.y};
}

} // namespace KaliLaska
