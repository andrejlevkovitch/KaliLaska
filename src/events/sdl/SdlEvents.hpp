// SdlEvents.hpp

#pragma once

#include "KaliLaska/Event.hpp"

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
} // namespace KaliLaska
