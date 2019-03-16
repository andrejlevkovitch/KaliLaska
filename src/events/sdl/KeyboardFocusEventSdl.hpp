// KeyboardFocusEventSdl.hpp

#include "KaliLaska/imp/KeyboardFocusEventImp.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
class KeyboardFocusEventSdl final : public KeyboardFocusEventImp {
public:
  KeyboardFocusEventSdl(Keyboard::Focus focus);
  KeyboardFocusEventSdl(const SDL_WindowEvent &event);

  Keyboard::Focus focus() const override;

private:
  SDL_WindowEvent event_;
};
} // namespace KaliLaska
