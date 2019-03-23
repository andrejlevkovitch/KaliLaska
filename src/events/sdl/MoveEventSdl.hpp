// MoveEvent.hpp

#include "events/imp/MoveEventImp.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
class MoveEventSdl final : public MoveEventImp {
public:
  MoveEventSdl(Point cur);
  MoveEventSdl(const SDL_WindowEvent &event);

  Point currentPos() const override;

private:
  SDL_WindowEvent event_;
};
} // namespace KaliLaska
