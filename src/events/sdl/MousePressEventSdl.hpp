// MousePressEventSdl.hpp

#pragma once

#include "events/imp/MousePressEventImp.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
class MousePressEventSdl final : public MousePressEventImp {
public:
  MousePressEventSdl(Mouse::Button button, Mouse::Click click, Point clickPos);

  /**\param buttons mask of currently pressed mouse buttons. This needed because
   * sdl event not store this information
   */
  MousePressEventSdl(SDL_MouseButtonEvent sdlEvent, uint32_t buttons);

  Mouse::Button  button() const override;
  Mouse::Buttons buttons() const override;
  Mouse::Click   click() const override;
  Point          clickPos() const override;

private:
  SDL_MouseButtonEvent event_;
  uint32_t             buttons_;
};
} // namespace KaliLaska
