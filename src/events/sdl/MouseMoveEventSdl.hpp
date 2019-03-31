// MouseMoveEventSdl.hpp

#pragma once

#include "events/imp/MouseMoveEventImp.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
class MouseMoveEventSdl : public MouseMoveEventImp {
public:
  MouseMoveEventSdl(Mouse::Buttons buttons, Point curPos, Point prevPos);

  MouseMoveEventSdl(SDL_MouseMotionEvent event);

  Mouse::Buttons buttons() const override;

  Point currentPos() const override;
  Point previousPos() const override;
  Point distance() const override;

private:
  SDL_MouseMotionEvent event_;
};
} // namespace KaliLaska
