// ApplicationSdl.cpp

#include "ApplicationSdl.hpp"
#include "KaliLaska/AbstractWindow.hpp"
#include "application/EventNotifyer.hpp"
#include "debug.hpp"
#include "events/sdl/EventConverterSdl.hpp"
#include "events/sdl/EventSdlFactory.hpp"
#include "graphics/rtree/GraphicsSceneRTreeFactory.hpp"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "logger/logger.hpp"
#include "window/sdl/WindowSdlFactory.hpp"
#include <GLES3/gl3.h>
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
    , windowImpFactory_{std::make_unique<WindowSdlFactory>()}
    , eventImpFactory_{std::make_unique<EventSdlFactory>()}
    , graphicsSceneImpFactory_{std::make_unique<GraphicsSceneRTreeFactory>()} {
  LOG_TRACE << "ApplicationSdl: konstructor";

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS)) {
    LOG_THROW(std::runtime_error, SDL_GetError());
  }

  int majorVersion{3};
  int minorVersion{0};
  int profileMask{SDL_GL_CONTEXT_PROFILE_ES};
  // set OpenGL attributes
  if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorVersion) < 0 ||
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorVersion) < 0 ||
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, profileMask) < 0 ||
      // TODO check that - at this moment no one gl context set
      SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1) < 0) {
    LOG_THROW(std::runtime_error, SDL_GetError());
  }

  int majorVersionCheck{};
  int minorVersionCheck{};
  int profileMaskCheck{};
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &majorVersionCheck);
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minorVersionCheck);
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profileMaskCheck);

  if (majorVersionCheck != majorVersion || minorVersionCheck != minorVersion ||
      profileMaskCheck != profileMask) {
    LOG_THROW(std::runtime_error, "OpenGL can not be correctly loaded");
  }

  LOG_INFO << "initialize opengl version " << majorVersion << '.'
           << minorVersion;

  // test creation
  testWin();
}

ApplicationSdl::~ApplicationSdl() {
  LOG_TRACE << "ApplicationSdl: destructor";
  SDL_Quit();
}

void ApplicationSdl::testWin() const {
  auto testWin = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_OPENGL);
  auto testCon = SDL_GL_CreateContext(testWin);
  if (testWin && testCon) {
    LOG_INFO << reinterpret_cast<const char *>(
        glGetString(GL_SHADING_LANGUAGE_VERSION));
    SDL_GL_DeleteContext(testCon);
    SDL_DestroyWindow(testWin);
  } else {
    SDL_GL_DeleteContext(testCon);
    SDL_DestroyWindow(testWin);
    LOG_THROW(std::runtime_error, "Window and Context can not be created");
  }
}

int ApplicationSdl::exec() {
  LOG_TRACE << "start main cikle";
  SDL_AddEventWatch(quitCallback, this);

  loop_ = true;
  SDL_Event sdlEvent;

  // in milliseconds
  int  waitTime{iterationTime_};
  auto lastTimePoint = std::chrono::system_clock::now();

  auto &io = ImGui::GetIO();

  // all events deliver emidiatly, but update calls for window only in regular
  // intervals
  while (loop_) {
    // event notifying have to be in main thread, especally because othrerwise
    // we not get quit event, after closed last window
    if (SDL_WaitEventTimeout(&sdlEvent, waitTime)) {
      // here we first check imgui for events, and, if imgui not capture the
      // event this event translate to KaliLaska events and send to window
      bool captured = false;
      switch (sdlEvent.type) {
      // TODO imgui also can get whele event
      case SDL_TEXTINPUT:
        if (io.WantTextInput) {
          ::ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
          captured = true;
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (io.WantCaptureMouse) {
          ::ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
          captured = true;
        }
        break;
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        if (io.WantCaptureKeyboard) {
          ::ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
          captured = true;
        }
        break;
      default:
        break;
      }

      if (!captured) {
        auto [window, event] =
            EventConverterSdl::convert(sdlEvent, *windowImpFactory_);
        EventNotifyer::notify(window, std::move(event));
      }
    }

    auto curDuration = std::chrono::system_clock::now() - lastTimePoint;
    if (curDuration >= std::chrono::milliseconds{iterationTime_}) {
      for (const auto &i : objects_) {
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
  LOG_TRACE << "ApplicationSdl: break main cikle";
  return return_code_;
}

void ApplicationSdl::exit(int code) {
  LOG_TRACE << "ApplicationSdl: exit";
  loop_        = false;
  return_code_ = code;
}

WindowImpFactory *ApplicationSdl::windowImpFactory() const {
  return windowImpFactory_.get();
}

EventImpFactory *ApplicationSdl::eventImpFactory() const {
  return eventImpFactory_.get();
}

GraphicsSceneImpFactory *ApplicationSdl::graphicsSceneImpFactory() const {
  return graphicsSceneImpFactory_.get();
}

void ApplicationSdl::setIterationTimeInterval(std::chrono::milliseconds time) {
  iterationTime_ = time.count();
}

std::chrono::milliseconds ApplicationSdl::iterationTimeInterval() const {
  return std::chrono::milliseconds{iterationTime_};
}

void ApplicationSdl::registerObject(Object *obj) {
  objects_.insert(obj);
}

void ApplicationSdl::unregisterObject(Object *obj) {
  objects_.erase(obj);
}
} // namespace KaliLaska
