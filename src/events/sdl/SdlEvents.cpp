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

ShowAction showAction(uint8_t sdlAction) {
  switch (sdlAction) {
  case SDL_WINDOWEVENT_SHOWN:
    return ShowAction::Shown;
  case SDL_WINDOWEVENT_HIDDEN:
    return ShowAction::Hidden;
    // case SDL_WINDOWEVENT_MINIMIZED:
    //  return ShowAction::Minimized;
    // case SDL_WINDOWEVENT_MAXIMIZED:
    //  return ShowAction::Maximized;
    // case SDL_WINDOWEVENT_RESTORED:
    //  return ShowAction::Restored;
  default:
    return ShowAction::Invalid;
  }
}

uint8_t sdlAction(ShowAction action) {
  switch (action) {
  case ShowAction::Shown:
    return SDL_WINDOWEVENT_SHOWN;
  case ShowAction::Hidden:
    return SDL_WINDOWEVENT_HIDDEN;
    // case ShowAction::Minimized:
    //  return SDL_WINDOWEVENT_MINIMIZED;
    // case ShowAction::Maximized:
    //  return SDL_WINDOWEVENT_MAXIMIZED;
    // case ShowAction::Restored:
    //  return SDL_WINDOWEVENT_RESTORED;
  default:
    return SDL_WINDOWEVENT_NONE;
  }
}

Mouse::Focus mouseFocus(uint8_t sdlMouseFocus) {
  switch (sdlMouseFocus) {
  case SDL_WINDOWEVENT_ENTER:
    return Mouse::Focus::Enter;
  case SDL_WINDOWEVENT_LEAVE:
    return Mouse::Focus::Leave;
  default:
    return Mouse::Focus::Invalid;
  }
}

uint8_t sdlMouseFocus(Mouse::Focus focus) {
  switch (focus) {
  case Mouse::Focus::Enter:
    return SDL_WINDOWEVENT_ENTER;
  case Mouse::Focus::Leave:
    return SDL_WINDOWEVENT_LEAVE;
  default:
    return SDL_WINDOWEVENT_NONE;
  }
}

Mouse::Click mouseClick(uint8_t sdlMouseClick) {
  switch (sdlMouseClick) {
  case 1:
    return Mouse::Click::Single;
  case 2:
    return Mouse::Click::Double;
  default:
    return Mouse::Click::Invalid;
  }
}

uint8_t sdlMouseClick(Mouse::Click click) {
  switch (click) {
  case Mouse::Click::Single:
    return 1;
  case Mouse::Click::Double:
    return 2;
  default:
    return 0;
  }
}
} // namespace KaliLaska
