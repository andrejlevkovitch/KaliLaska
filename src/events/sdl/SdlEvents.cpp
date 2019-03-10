// SdlEvents.cpp

#include "SdlEvents.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
Mouse::Buttons mouseButtons(uint32_t sdlButtons) {
  Mouse::Buttons retval{};
  retval += (sdlButtons & SDL_BUTTON_LMASK) ? Mouse::Button::Left : 0;
  retval += (sdlButtons & SDL_BUTTON_RMASK) ? Mouse::Button::Right : 0;
  retval += (sdlButtons & SDL_BUTTON_MMASK) ? Mouse::Button::Middle : 0;
  return retval;
}

uint32_t sdlButtons(Mouse::Buttons buttons) {
  uint32_t retval{};
  retval += (buttons & Mouse::Button::Left) ? SDL_BUTTON_LMASK : 0;
  retval += (buttons & Mouse::Button::Right) ? SDL_BUTTON_RMASK : 0;
  retval += (buttons & Mouse::Button::Middle) ? SDL_BUTTON_MMASK : 0;
  return retval;
}

Mouse::Button mouseButton(uint8_t sdlButton) {
  switch (sdlButton) {
  case SDL_BUTTON_LEFT:
    return Mouse::Button::Left;
  case SDL_BUTTON_RIGHT:
    return Mouse::Button::Right;
  case SDL_BUTTON_MIDDLE:
    return Mouse::Button::Middle;
  default:
    return Mouse::Button::Invalid;
  }
}

uint8_t sdlButton(Mouse::Button button) {
  switch (button) {
  case Mouse::Button::Left:
    return SDL_BUTTON_LEFT;
  case Mouse::Button::Right:
    return SDL_BUTTON_RIGHT;
  case Mouse::Button::Middle:
    return SDL_BUTTON_MIDDLE;
  default:
    return 0;
  }
}
} // namespace KaliLaska
