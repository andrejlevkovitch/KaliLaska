// ResizeEventSdl.hpp

#pragma once

#include "KaliLaska/imp/ResizeEventImp.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
class ResizeEventSdl : public ResizeEventImp {
public:
  ResizeEventSdl(Size news);

  ResizeEventSdl(SDL_WindowEvent event);

  Size currentSize() const override;

private:
  SDL_WindowEvent event_;
};
} // namespace KaliLaska
