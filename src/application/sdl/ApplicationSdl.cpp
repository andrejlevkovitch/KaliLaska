// ApplicationSdl.cpp

#include "ApplicationSdl.hpp"
#include "KaliLaska/EventNotifyer.hpp"
#include "debug.hpp"
#include "events/sdl/EventConverterSdl.hpp"
#include "events/sdl/EventSdlFactory.hpp"
#include "window/sdl/WindowSdlFactory.hpp"
#include <SDL2/SDL.h>
#include <stdexcept>
#include <thread>

#define WAIT_TIMEOUT 300

namespace KaliLaska {

int quitCallback(void *app, SDL_Event *event) {
  if (event->type == SDL_EventType::SDL_QUIT) {
    DEBUG_OUT("exit sdl event");
    reinterpret_cast<ApplicationSdl *>(app)->exit(0);
  }
  return {};
}

int eventFilter(void *factory, SDL_Event *sdlEvent) {
  auto [window, event] = EventConverterSdl::convert(
      *sdlEvent, *reinterpret_cast<const WindowSdlFactory *>(factory));
  if (window && event) {
    EventNotifyer::notify(window, std::move(event));
    return 0;
  }
  return 1;
}

ApplicationSdl::ApplicationSdl()
    : loop_{false}
    , return_code_{}
    , windowFactory_{std::make_unique<WindowSdlFactory>()}
    , eventFactory_{std::make_unique<EventSdlFactory>()} {
  if (::SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS)) {
    throw std::runtime_error{SDL_GetError()};
  }
}

ApplicationSdl::~ApplicationSdl() {
  ::SDL_Quit();
}

int ApplicationSdl::exec() {
  SDL_AddEventWatch(quitCallback, this);
  SDL_SetEventFilter(eventFilter, windowFactory_.get());

  loop_ = true;
  SDL_Event event;
  while (loop_) {
    // we use with timeout because quitcallback work in other thread
    SDL_WaitEventTimeout(&event, WAIT_TIMEOUT);
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
