// ApplicationSdl.cpp

#include "ApplicationSdl.hpp"
#include "KaliLaska/EventNotifyer.hpp"
#include "debug.hpp"
#include "events/sdl/EventConverterSdl.hpp"
#include "events/sdl/EventSdlFactory.hpp"
#include "window/sdl/WindowSdlFactory.hpp"
#include <SDL2/SDL.h>
#include <cstdlib>
#include <stdexcept>
#include <thread>

#define WAIT_TIMEOUT 300

namespace KaliLaska {

int quitCallback(void *app, SDL_Event *event) {
  if (event->type == SDL_EventType::SDL_QUIT) {
    DEBUG_OUT("exit sdl event");
    reinterpret_cast<ApplicationSdl *>(app)->exit(EXIT_SUCCESS);
  }
  return {};
}

ApplicationSdl::ApplicationSdl()
    : loop_{false}
    , return_code_{EXIT_SUCCESS}
    , windowFactory_{std::make_unique<WindowSdlFactory>()}
    , eventFactory_{std::make_unique<EventSdlFactory>()} {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS)) {
    throw std::runtime_error{SDL_GetError()};
  }
}

ApplicationSdl::~ApplicationSdl() {
  SDL_Quit();
}

int ApplicationSdl::exec() {
  SDL_AddEventWatch(quitCallback, this);

  loop_ = true;
  SDL_Event sdlEvent;
  while (loop_) {
    // event notifying have to be in main thread, especally because othrerwise
    // we not get quit event, after closed last window
    if (SDL_WaitEventTimeout(&sdlEvent, WAIT_TIMEOUT)) {
      auto [window, event] =
          EventConverterSdl::convert(sdlEvent, *windowFactory_);
      EventNotifyer::notify(window, std::move(event));
    }
  }
  return return_code_;
}

void ApplicationSdl::exit(int code) {
  loop_        = false;
  return_code_ = code;
}

WindowImpFactory *ApplicationSdl::windowFactory() const {
  return windowFactory_.get();
}

EventImpFactory *ApplicationSdl::eventFactory() const {
  return eventFactory_.get();
}
} // namespace KaliLaska
