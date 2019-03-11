// MouseFocusEventSdl.cpp

#include "MouseFocusEventSdl.hpp"
#include "SdlEvents.hpp"

namespace KaliLaska {
MouseFocusEventSdl::MouseFocusEventSdl(Mouse::Focus focus)
    : event_{} {
  event_.event = sdlMouseFocus(focus);
}

MouseFocusEventSdl::MouseFocusEventSdl(const SDL_WindowEvent &event)
    : event_{event} {
}

Mouse::Focus MouseFocusEventSdl::focus() const {
  return mouseFocus(event_.event);
}
} // namespace KaliLaska
