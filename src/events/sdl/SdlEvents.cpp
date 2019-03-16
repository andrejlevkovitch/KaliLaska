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

Keyboard::Focus keyboardFocus(uint8_t sdlKeyboardFocus) {
  switch (sdlKeyboardFocus) {
  case SDL_WINDOWEVENT_FOCUS_GAINED:
    return Keyboard::Focus::Gained;
    break;
  case SDL_WINDOWEVENT_FOCUS_LOST:
    return Keyboard::Focus::Lost;
  default:
    return Keyboard::Focus::Invalid;
  }
}

uint8_t sdlKeyboardFocus(Keyboard::Focus focus) {
  switch (focus) {
  case Keyboard::Focus::Gained:
    return SDL_WINDOWEVENT_FOCUS_GAINED;
  case Keyboard::Focus::Lost:
    return SDL_WINDOWEVENT_FOCUS_LOST;
  default:
    return SDL_WINDOWEVENT_NONE;
  }
}

Keyboard::Modifyers keyModifyers(uint16_t sdlKeyMod) {
  Keyboard::Modifyers retval{};
  retval += (sdlKeyMod & KMOD_CTRL) ? Keyboard::Mod::Ctrl : 0;
  retval += (sdlKeyMod & KMOD_SHIFT) ? Keyboard::Mod::Shift : 0;
  retval += (sdlKeyMod & KMOD_ALT) ? Keyboard::Mod::Alt : 0;
  return retval;
}

uint16_t sdlKeyModifyers(Keyboard::Modifyers mode) {
  uint16_t retval{};
  retval += (mode & Keyboard::Mod::Ctrl) ? KMOD_CTRL : 0;
  retval += (mode & Keyboard::Mod::Shift) ? KMOD_SHIFT : 0;
  retval += (mode & Keyboard::Mod::Alt) ? KMOD_ALT : 0;
  return retval;
}

Keyboard::Key keyCode(SDL_Scancode sdlKeyCode) {
  switch (sdlKeyCode) {
  case SDL_SCANCODE_0:
    return Keyboard::Key::Key_0;
  case SDL_SCANCODE_1:
    return Keyboard::Key::Key_1;
  case SDL_SCANCODE_2:
    return Keyboard::Key::Key_2;
  case SDL_SCANCODE_3:
    return Keyboard::Key::Key_3;
  case SDL_SCANCODE_4:
    return Keyboard::Key::Key_4;
  case SDL_SCANCODE_5:
    return Keyboard::Key::Key_5;
  case SDL_SCANCODE_6:
    return Keyboard::Key::Key_6;
  case SDL_SCANCODE_7:
    return Keyboard::Key::Key_7;
  case SDL_SCANCODE_8:
    return Keyboard::Key::Key_8;
  case SDL_SCANCODE_9:
    return Keyboard::Key::Key_9;
  case SDL_SCANCODE_A:
    return Keyboard::Key::Key_A;
  case SDL_SCANCODE_B:
    return Keyboard::Key::Key_B;
  case SDL_SCANCODE_C:
    return Keyboard::Key::Key_C;
  case SDL_SCANCODE_D:
    return Keyboard::Key::Key_D;
  case SDL_SCANCODE_E:
    return Keyboard::Key::Key_E;
  case SDL_SCANCODE_F:
    return Keyboard::Key::Key_F;
  case SDL_SCANCODE_G:
    return Keyboard::Key::Key_G;
  case SDL_SCANCODE_H:
    return Keyboard::Key::Key_H;
  case SDL_SCANCODE_I:
    return Keyboard::Key::Key_I;
  case SDL_SCANCODE_J:
    return Keyboard::Key::Key_J;
  case SDL_SCANCODE_K:
    return Keyboard::Key::Key_K;
  case SDL_SCANCODE_L:
    return Keyboard::Key::Key_L;
  case SDL_SCANCODE_M:
    return Keyboard::Key::Key_M;
  case SDL_SCANCODE_N:
    return Keyboard::Key::Key_N;
  case SDL_SCANCODE_O:
    return Keyboard::Key::Key_O;
  case SDL_SCANCODE_P:
    return Keyboard::Key::Key_P;
  case SDL_SCANCODE_Q:
    return Keyboard::Key::Key_Q;
  case SDL_SCANCODE_R:
    return Keyboard::Key::Key_R;
  case SDL_SCANCODE_S:
    return Keyboard::Key::Key_S;
  case SDL_SCANCODE_T:
    return Keyboard::Key::Key_T;
  case SDL_SCANCODE_U:
    return Keyboard::Key::Key_U;
  case SDL_SCANCODE_V:
    return Keyboard::Key::Key_V;
  case SDL_SCANCODE_W:
    return Keyboard::Key::Key_W;
  case SDL_SCANCODE_X:
    return Keyboard::Key::Key_X;
  case SDL_SCANCODE_Y:
    return Keyboard::Key::Key_Y;
  case SDL_SCANCODE_Z:
    return Keyboard::Key::Key_Z;
  case SDL_SCANCODE_SPACE:
    return Keyboard::Key::Key_Space;
  case SDL_SCANCODE_RETURN:
    return Keyboard::Key::Key_Enter;
  case SDL_SCANCODE_UP:
    return Keyboard::Key::Key_Up;
  case SDL_SCANCODE_DOWN:
    return Keyboard::Key::Key_Down;
  case SDL_SCANCODE_LEFT:
    return Keyboard::Key::Key_Left;
  case SDL_SCANCODE_RIGHT:
    return Keyboard::Key::Key_Right;
  case SDL_SCANCODE_LCTRL:
  case SDL_SCANCODE_RCTRL:
    return Keyboard::Key::Key_Ctrl;
  case SDL_SCANCODE_LALT:
  case SDL_SCANCODE_RALT:
    return Keyboard::Key::Key_Alt;
  case SDL_SCANCODE_LSHIFT:
  case SDL_SCANCODE_RSHIFT:
    return Keyboard::Key::Key_Shift;
  default:
    return Keyboard::Key::Invalid;
  }
}

SDL_Scancode sdlKeyCode(Keyboard::Key key) {
  switch (key) {
  case Keyboard::Key::Key_0:
    return SDL_SCANCODE_0;
  case Keyboard::Key::Key_1:
    return SDL_SCANCODE_1;
  case Keyboard::Key::Key_2:
    return SDL_SCANCODE_2;
  case Keyboard::Key::Key_3:
    return SDL_SCANCODE_3;
  case Keyboard::Key::Key_4:
    return SDL_SCANCODE_4;
  case Keyboard::Key::Key_5:
    return SDL_SCANCODE_5;
  case Keyboard::Key::Key_6:
    return SDL_SCANCODE_6;
  case Keyboard::Key::Key_7:
    return SDL_SCANCODE_7;
  case Keyboard::Key::Key_8:
    return SDL_SCANCODE_8;
  case Keyboard::Key::Key_9:
    return SDL_SCANCODE_9;
  case Keyboard::Key::Key_A:
    return SDL_SCANCODE_A;
  case Keyboard::Key::Key_B:
    return SDL_SCANCODE_B;
  case Keyboard::Key::Key_C:
    return SDL_SCANCODE_C;
  case Keyboard::Key::Key_D:
    return SDL_SCANCODE_D;
  case Keyboard::Key::Key_E:
    return SDL_SCANCODE_E;
  case Keyboard::Key::Key_F:
    return SDL_SCANCODE_F;
  case Keyboard::Key::Key_G:
    return SDL_SCANCODE_G;
  case Keyboard::Key::Key_H:
    return SDL_SCANCODE_H;
  case Keyboard::Key::Key_J:
    return SDL_SCANCODE_J;
  case Keyboard::Key::Key_I:
    return SDL_SCANCODE_I;
  case Keyboard::Key::Key_K:
    return SDL_SCANCODE_K;
  case Keyboard::Key::Key_L:
    return SDL_SCANCODE_L;
  case Keyboard::Key::Key_M:
    return SDL_SCANCODE_M;
  case Keyboard::Key::Key_N:
    return SDL_SCANCODE_N;
  case Keyboard::Key::Key_O:
    return SDL_SCANCODE_O;
  case Keyboard::Key::Key_P:
    return SDL_SCANCODE_P;
  case Keyboard::Key::Key_Q:
    return SDL_SCANCODE_Q;
  case Keyboard::Key::Key_R:
    return SDL_SCANCODE_R;
  case Keyboard::Key::Key_S:
    return SDL_SCANCODE_S;
  case Keyboard::Key::Key_T:
    return SDL_SCANCODE_T;
  case Keyboard::Key::Key_U:
    return SDL_SCANCODE_U;
  case Keyboard::Key::Key_V:
    return SDL_SCANCODE_V;
  case Keyboard::Key::Key_W:
    return SDL_SCANCODE_W;
  case Keyboard::Key::Key_X:
    return SDL_SCANCODE_X;
  case Keyboard::Key::Key_Y:
    return SDL_SCANCODE_Y;
  case Keyboard::Key::Key_Z:
    return SDL_SCANCODE_Z;
  case Keyboard::Key::Key_Space:
    return SDL_SCANCODE_SPACE;
  case Keyboard::Key::Key_Enter:
    return SDL_SCANCODE_RETURN;
  case Keyboard::Key::Key_Up:
    return SDL_SCANCODE_UP;
  case Keyboard::Key::Key_Down:
    return SDL_SCANCODE_DOWN;
  case Keyboard::Key::Key_Left:
    return SDL_SCANCODE_LEFT;
  case Keyboard::Key::Key_Right:
    return SDL_SCANCODE_RIGHT;
  case Keyboard::Key::Key_Ctrl:
    return SDL_SCANCODE_LCTRL;
  case Keyboard::Key::Key_Alt:
    return SDL_SCANCODE_LALT;
  case Keyboard::Key::Key_Shift:
    return SDL_SCANCODE_LSHIFT;
  case Keyboard::Key::Invalid:
    break;
  }
  return SDL_SCANCODE_UNKNOWN;
}
} // namespace KaliLaska
