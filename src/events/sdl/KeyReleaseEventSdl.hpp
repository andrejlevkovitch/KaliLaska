// KeyReleaseEventSdl.hpp

#pragma once

#include "KaliLaska/imp/KeyReleaseEventImp.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
class KeyReleaseEventSdl final : public KeyReleaseEventImp {
public:
  /**\brief konstructor for user custom events
   */
  KeyReleaseEventSdl(Keyboard::Key key, Keyboard::Modifyers mod);

  KeyReleaseEventSdl(const SDL_KeyboardEvent &event);

  Keyboard::Modifyers modifyers() const override;
  Keyboard::Key       key() const override;

private:
  SDL_KeyboardEvent event_;
};
} // namespace KaliLaska
