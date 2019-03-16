// KeyboardFocusEvent.cpp

#include "KeyboardFocusEventSdl.hpp"
#include "SdlEvents.hpp"

namespace KaliLaska {
KeyboardFocusEventSdl::KeyboardFocusEventSdl(Keyboard::Focus focus)
    : event_{} {
  event_.event = sdlKeyboardFocus(focus);
}

KeyboardFocusEventSdl::KeyboardFocusEventSdl(const SDL_WindowEvent &event)
    : event_{event} {
}

Keyboard::Focus KeyboardFocusEventSdl::focus() const {
  return keyboardFocus(event_.event);
}
} // namespace KaliLaska
