// MouseMoveEventSdl.cpp

#include "MouseMoveEventSdl.hpp"
#include "SdlEvents.hpp"

namespace KaliLaska {
MouseMoveEventSdl::MouseMoveEventSdl(Mouse::Buttons buttons,
                                     Point          curPos,
                                     Point          prevPos)
    : event_{} {
  event_.state = sdlButtons(buttons);
  event_.x     = curPos.x();
  event_.y     = curPos.y();
  event_.xrel  = curPos.x() - prevPos.x();
  event_.yrel  = curPos.y() - prevPos.y();
}

MouseMoveEventSdl::MouseMoveEventSdl(SDL_MouseMotionEvent event)
    : event_{event} {
}

Mouse::Buttons MouseMoveEventSdl::buttons() const {
  return mouseButtons(event_.state);
}

Point MouseMoveEventSdl::currentPos() const {
  return Point{event_.x, event_.y};
}

Point MouseMoveEventSdl::previousPos() const {
  return Point{event_.x - event_.xrel, event_.y - event_.yrel};
}
} // namespace KaliLaska
