// ApplicationSdl.cpp

#include "ApplicationSdl.hpp"
#include "KaliLaska/Window.hpp"
#include "application/EventNotifyer.hpp"
#include "debug.hpp"
#include "events/sdl/EventConverterSdl.hpp"
#include "events/sdl/EventSdlFactory.hpp"
#include "graphics/rtree/GraphicsSceneRTreeFactory.hpp"
#include "window/sdl/WindowSdlFactory.hpp"
#include <SDL2/SDL.h>
#include <chrono>
#include <cstdlib>
#include <stdexcept>
#include <thread>

#define DEFAULT_WAIT_TIMEOUT 50

namespace KaliLaska {

int quitCallback(void *app, SDL_Event *event) {
  if (event->type == SDL_EventType::SDL_QUIT) {
    reinterpret_cast<ApplicationSdl *>(app)->exit(EXIT_SUCCESS);
  }
  return {};
}

ApplicationSdl::ApplicationSdl()
    : loop_{false}
    , return_code_{EXIT_SUCCESS}
    , iterationTime_{DEFAULT_WAIT_TIMEOUT}
    , windowFactory_{std::make_unique<WindowSdlFactory>()}
    , eventFactory_{std::make_unique<EventSdlFactory>()}
    , sceneFactory_{std::make_unique<GraphicsSceneRTreeFactory>()} {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS)) {
    throw std::runtime_error{SDL_GetError()};
  }

  int majorVersion{3};
  int minorVersion{0};
  int profileMask{SDL_GL_CONTEXT_PROFILE_ES};
  // set OpenGL attributes
  if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorVersion) < 0 ||
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorVersion) < 0 ||
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, profileMask)) {
    throw std::runtime_error{SDL_GetError()};
  }

  int majorVersionCheck{};
  int minorVersionCheck{};
  int profileMaskCheck{};
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &majorVersionCheck);
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minorVersionCheck);
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profileMaskCheck);

  if (majorVersionCheck != majorVersion || minorVersionCheck != minorVersion ||
      profileMaskCheck != profileMask) {
    throw std::runtime_error{"OpenGL can not be correctly loaded"};
  }
}

ApplicationSdl::~ApplicationSdl() {
  SDL_Quit();
}

int ApplicationSdl::exec() {
  SDL_AddEventWatch(quitCallback, this);

  loop_ = true;
  SDL_Event sdlEvent;

  // in milliseconds
  int  waitTime{iterationTime_};
  auto lastTimePoint = std::chrono::system_clock::now();

  // all events deliver emidiatly, but update calls for window only in regular
  // intervals
  while (loop_) {
    // event notifying have to be in main thread, especally because othrerwise
    // we not get quit event, after closed last window
    if (SDL_WaitEventTimeout(&sdlEvent, waitTime)) {
      auto [window, event] =
          EventConverterSdl::convert(sdlEvent, *windowFactory_);
      EventNotifyer::notify(window, std::move(event));
    }

    auto curDuration = std::chrono::system_clock::now() - lastTimePoint;
    if (curDuration >= std::chrono::milliseconds{iterationTime_}) {
      for (const auto &i : windowFactory_->allWindows()) {
        if (i) {
          i->update();
        }
      }
      lastTimePoint = std::chrono::system_clock::now();
      waitTime      = iterationTime_;
    } else {
      waitTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::milliseconds{iterationTime_} - curDuration)
                     .count();
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

GraphicsSceneImpFactory *ApplicationSdl::sceneFactory() {
  return sceneFactory_.get();
}

void ApplicationSdl::setIterationTimeInterval(std::chrono::milliseconds time) {
  iterationTime_ = time.count();
}

std::chrono::milliseconds ApplicationSdl::iterationTimeInterval() const {
  return std::chrono::milliseconds{iterationTime_};
}
} // namespace KaliLaska
