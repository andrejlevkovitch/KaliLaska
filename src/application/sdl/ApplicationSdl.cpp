// ApplicationSdl.cpp

#include "ApplicationSdl.hpp"
#include "KaliLaska/EventNotifyer.hpp"
#include "debug.hpp"
#include "events/sdl/EventConverterSdl.hpp"
#include "events/sdl/EventSdlFactory.hpp"
#include "window/sdl/WindowSdlFactory.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <stdexcept>
#include <thread>

namespace KaliLaska {

int quitCallback(void *app, SDL_Event *event) {
  if (event && event->type == SDL_EventType::SDL_QUIT) {
    reinterpret_cast<ApplicationSdl *>(app)->exit(0);
  }
  return {};
}

int eventFilter(void *factory, SDL_Event *sdlEvent) {
  if (sdlEvent) {
    auto [window, event] = EventConverterSdl::convert(
        *sdlEvent, *reinterpret_cast<const WindowSdlFactory *>(factory));
    if (window && event) {
      EventNotifyer::notify(window, std::move(event));
      return 0;
    }
    return 1;
  }
  return {};
}

ApplicationSdl::ApplicationSdl()
    : cickleInterval_{100}
    , loop_{false}
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

  auto lastTick = std::chrono::system_clock::now();
  loop_         = true;
  while (loop_) {
    auto sleepInterval = std::chrono::milliseconds{cickleInterval_} -
                         (std::chrono::system_clock::now() - lastTick);
    std::this_thread::sleep_for(sleepInterval);
    lastTick = std::chrono::system_clock::now();
    handleEventQueue();
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

void ApplicationSdl::handleEventQueue() {
  SDL_Event event;
  while (::SDL_PollEvent(&event)) {
  }
}

int ApplicationSdl::ups() const {
  return 1000 / cickleInterval_.load();
}

void ApplicationSdl::setUps(int ups) {
  cickleInterval_ = 1000 / ups;
}
} // namespace KaliLaska
