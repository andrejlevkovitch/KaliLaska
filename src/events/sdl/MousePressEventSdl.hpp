// MousePressEventSdl.hpp

#pragma once

#include "KaliLaska/MousePressEventImp.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
class MousePressEventSdl final : public MousePressEventImp {
public:
  MousePressEventSdl(Mouse::Button button, Point clickPos);

  MousePressEventSdl(SDL_MouseButtonEvent sdlEvent);

  Mouse::Button  button() const override;
  Mouse::Buttons buttons() const override;
  Point          clickPos() const override;

private:
  SDL_MouseButtonEvent event_;
};
} // namespace KaliLaska
