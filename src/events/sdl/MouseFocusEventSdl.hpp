// MouseFocusEventSdl.hpp

#pragma once

#include "KaliLaska/imp/MouseFocusEventImp.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
class MouseFocusEventSdl : public MouseFocusEventImp {
public:
  MouseFocusEventSdl(Mouse::Focus focus);
  MouseFocusEventSdl(const SDL_WindowEvent &event);

  Mouse::Focus focus() const override;

private:
  SDL_WindowEvent event_;
};
} // namespace KaliLaska
