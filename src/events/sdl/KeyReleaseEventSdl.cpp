// KeyReleaseEventSdl.hpp

#include "KeyReleaseEventSdl.hpp"
#include "SdlEvents.hpp"

namespace KaliLaska {
KeyReleaseEventSdl::KeyReleaseEventSdl(Keyboard::Key       key,
                                       Keyboard::Modifyers mod)
    : event_{} {
  event_.keysym.mod      = sdlKeyModifyers(mod);
  event_.keysym.scancode = sdlKeyCode(key);
}

KeyReleaseEventSdl::KeyReleaseEventSdl(const SDL_KeyboardEvent &event)
    : event_{event} {
}

Keyboard::Key KeyReleaseEventSdl::key() const {
  return keyCode(event_.keysym.scancode);
}

Keyboard::Modifyers KeyReleaseEventSdl::modifyers() const {
  return keyModifyers(event_.keysym.mod);
}
} // namespace KaliLaska
