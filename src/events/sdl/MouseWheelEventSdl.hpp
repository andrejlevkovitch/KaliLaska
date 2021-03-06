// MouseWheelEventSdl.hpp

#pragma once

#include "events/imp/MouseWheelEventImp.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
class MouseWheelEventSdl final : public MouseWheelEventImp {
public:
  MouseWheelEventSdl(Mouse::Scale scale);

  MouseWheelEventSdl(SDL_MouseWheelEvent event, uint32_t buttons, Point pos);

  Point          position() const override;
  Mouse::Buttons buttons() const override;
  Mouse::Scale   scale() const override;

private:
  SDL_MouseWheelEvent event_;
  uint32_t            buttons_;
  Point               pos_;
};
} // namespace KaliLaska
