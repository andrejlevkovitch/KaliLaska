// SdlEvents.hpp

#pragma once

#include "KaliLaska/Event.hpp"

namespace KaliLaska {
Mouse::Buttons mouseButtons(uint32_t sdlButtons);
uint32_t       sdlButtons(Mouse::Buttons button);

Mouse::Button mouseButton(uint8_t sdlButton);
uint8_t       sdlButton(Mouse::Button button);
} // namespace KaliLaska
