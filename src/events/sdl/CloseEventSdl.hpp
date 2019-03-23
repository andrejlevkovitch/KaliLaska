// CloseEventSdl.hpp

#pragma once

#include "events/imp/CloseEventImp.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
class CloseEventSdl final : public CloseEventImp {
public:
  CloseEventSdl();

  CloseEventSdl(const SDL_WindowEvent &event);

private:
  SDL_WindowEvent event_;
};
} // namespace KaliLaska
