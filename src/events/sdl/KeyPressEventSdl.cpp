// KeyPressEventSdl.cpp

#include "KeyPressEventSdl.hpp"
#include "SdlEvents.hpp"

namespace KaliLaska {
KeyPressEventSdl::KeyPressEventSdl(Keyboard::Key       key,
                                   Keyboard::Modifyers mod,
                                   bool                isRepeat)
    : event_{} {
  event_.keysym.mod      = sdlKeyModifyers(mod);
  event_.keysym.scancode = sdlKeyCode(key);
  event_.repeat          = isRepeat;
}

KeyPressEventSdl::KeyPressEventSdl(const SDL_KeyboardEvent &event)
    : event_{event} {
}

Keyboard::Key KeyPressEventSdl::key() const {
  return keyCode(event_.keysym.scancode);
}

Keyboard::Modifyers KeyPressEventSdl::modifyers() const {
  return keyModifyers(event_.keysym.mod);
}

bool KeyPressEventSdl::isRepeat() const {
  return event_.repeat;
}
} // namespace KaliLaska
