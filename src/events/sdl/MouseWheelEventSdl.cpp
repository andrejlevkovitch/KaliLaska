// MouseWheelEventSdl.cpp

#include "MouseWheelEventSdl.hpp"
#include "SdlEvents.hpp"

namespace KaliLaska {
MouseWheelEventSdl::MouseWheelEventSdl(Mouse::Scale scale)
    : event_{} {
  if (scale != Mouse::Scale::Invalid) {
    event_.y = (scale == Mouse::Scale::ScaleDown) ? -1 : 1;
  }
}

MouseWheelEventSdl::MouseWheelEventSdl(SDL_MouseWheelEvent event)
    : event_{event} {
}

Point MouseWheelEventSdl::position() const {
  int x{};
  int y{};
  SDL_GetMouseState(&x, &y);
  return Point{x, y};
}

Mouse::Buttons MouseWheelEventSdl::buttons() const {
  return mouseButtons(SDL_GetMouseState(nullptr, nullptr));
}

Mouse::Scale MouseWheelEventSdl::scale() const {
  if (event_.y > 0) {
    return Mouse::Scale::ScaleUp;
  } else if (event_.y < 0) {
    return Mouse::Scale::ScaleDown;
  }
  return Mouse::Scale::Invalid;
}
} // namespace KaliLaska
