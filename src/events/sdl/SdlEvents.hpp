// SdlEvents.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include <SDL2/SDL.h>

namespace KaliLaska {
Mouse::Buttons mouseButtons(uint32_t sdlButtons);
uint32_t       sdlButtons(Mouse::Buttons button);

Mouse::Button mouseButton(uint8_t sdlButton);
uint8_t       sdlButton(Mouse::Button button);

ShowAction showAction(uint8_t sdlAction);
uint8_t    sdlAction(ShowAction action);

Mouse::Focus mouseFocus(uint8_t sdlMouseFocus);
uint8_t      sdlMouseFocus(Mouse::Focus focus);

Mouse::Click mouseClick(uint8_t sdlMouseClick);
uint8_t      sdlMouseClick(Mouse::Click click);

Keyboard::Focus keyboardFocus(uint8_t sdlKeyboardFocus);
uint8_t         sdlKeyboardFocus(Keyboard::Focus focus);

Keyboard::Modifyers keyModifyers(uint16_t sdlKeyMod);
uint16_t            sdlKeyModifyers(Keyboard::Modifyers mode);

Keyboard::Key keyCode(SDL_Scancode sdlKeyCode);
SDL_Scancode  sdlKeyCode(Keyboard::Key key);
} // namespace KaliLaska
