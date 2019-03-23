// ShowEventSdl.hpp

#pragma once

#include "events/imp/ShowEventImp.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
class ShowEventSdl final : public ShowEventImp {
public:
  ShowEventSdl(ShowAction action);
  ShowEventSdl(const SDL_WindowEvent &event);

  ShowAction action() const override;

private:
  SDL_WindowEvent event_;
};
} // namespace KaliLaska
