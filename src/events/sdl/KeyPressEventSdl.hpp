// KeyPressEventSdl.hpp

#pragma once

#include "KaliLaska/imp/KeyPressEventImp.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
class KeyPressEventSdl final : public KeyPressEventImp {
public:
  /**\brief konstructor for user custom events
   */
  KeyPressEventSdl(Keyboard::Key key, Keyboard::Modifyers mod, bool isRepeat);

  KeyPressEventSdl(const SDL_KeyboardEvent &event);

  Keyboard::Key       key() const;
  Keyboard::Modifyers modifyers() const;
  bool                isRepeat() const;

private:
  SDL_KeyboardEvent event_;
};
} // namespace KaliLaska
