// MouseWheelEventSdl.cpp

#include "MouseWheelEventSdl.hpp"
#include "SdlEvents.hpp"

namespace KaliLaska {
MouseWheelEventSdl::MouseWheelEventSdl(Mouse::Scale scale)
    : event_{}
    , buttons_{}
    , pos_{} {
  if (scale != Mouse::Scale::Invalid) {
    event_.y = (scale == Mouse::Scale::ScaleDown) ? -1 : 1;
  }
}

MouseWheelEventSdl::MouseWheelEventSdl(SDL_MouseWheelEvent event,
                                       uint32_t            buttons,
                                       Point               pos)
    : event_{event}
    , buttons_{buttons}
    , pos_{pos} {
}

Point MouseWheelEventSdl::position() const {
  return pos_;
}

Mouse::Buttons MouseWheelEventSdl::buttons() const {
  return mouseButtons(buttons_);
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
