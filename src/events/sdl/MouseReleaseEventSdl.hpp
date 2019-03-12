// MouseReleaseEventSdl.hpp

#pragma once

#include "KaliLaska/imp/MouseReleaseEventImp.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
class MouseReleaseEventSdl final : public MouseReleaseEventImp {
public:
  MouseReleaseEventSdl(Mouse::Button button, Point clickPos);

  /**\param buttons mask of currently pressed mouse buttons. This needed because
   * sdl event not store this information
   */
  MouseReleaseEventSdl(SDL_MouseButtonEvent event, uint32_t buttons);

  Mouse::Button  button() const;
  Mouse::Buttons buttons() const;
  Point          clickPos() const;

private:
  SDL_MouseButtonEvent event_;
  uint32_t             buttons_;
};
} // namespace KaliLaska
