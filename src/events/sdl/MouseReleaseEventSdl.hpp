// MouseReleaseEventSdl.hpp

#pragma once

#include "KaliLaska/imp/MouseReleaseEventImp.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
class MouseReleaseEventSdl final : public MouseReleaseEventImp {
public:
  MouseReleaseEventSdl(Mouse::Button button, Point clickPos);

  MouseReleaseEventSdl(SDL_MouseButtonEvent event);

  Mouse::Button  button() const;
  Mouse::Buttons buttons() const;
  Point          clickPos() const;

private:
  SDL_MouseButtonEvent event_;
};
} // namespace KaliLaska
