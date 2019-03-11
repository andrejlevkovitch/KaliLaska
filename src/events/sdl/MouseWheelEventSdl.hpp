// MouseWheelEventSdl.hpp

#pragma once

#include "KaliLaska/imp/MouseWheelEventImp.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
class MouseWheelEventSdl final : public MouseWheelEventImp {
public:
  MouseWheelEventSdl(Mouse::Scale scale);

  MouseWheelEventSdl(SDL_MouseWheelEvent event);

  Point          position() const override;
  Mouse::Buttons buttons() const override;
  Mouse::Scale   scale() const override;

private:
  ::SDL_MouseWheelEvent event_;
};
} // namespace KaliLaska
