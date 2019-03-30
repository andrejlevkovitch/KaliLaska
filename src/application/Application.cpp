// Application.cpp

#include "KaliLaska/Application.hpp"
#include "EventNotifyer.hpp"
#include "KaliLaska/Event.hpp"
#include "imp/ApplicationImp.hpp"
#include "sdl/ApplicationSdl.hpp"
#include <GL/gl3w.h>
#include <chrono>
#include <stdexcept>
#include <string.h>

#define DEFAULT_UPS 10

namespace KaliLaska {

inline static Application *instancePtr = nullptr;

Application::Application(int argc, char *argv[])
    : imp_{} {
  if (!instancePtr) {
    instancePtr = this;
  } else {
    throw std::runtime_error{"Application can not be initialized twice"};
  }
  try {
    // TODO maybe we can use factory or somthing else?
    imp_ = std::make_unique<ApplicationSdl>();
    parseArguments(argc, argv);
  } catch (std::runtime_error &) {
    throw;
  }

  // TODO here I also initialize gl3w - I do not like it
  gl3wInit();
}

Application::~Application() {
}

Application *Application::instance() {
  return instancePtr;
}

int Application::exec() {
  if (instancePtr) {
    return instancePtr->imp_->exec();
  } else {
    throw std::runtime_error{"Application not initialized"};
  }
}

void Application::parseArguments(int argc, char *argv[]) {
  // TODO not implement
  try {
    if (argc > 1) {
      for (int i{}; i < argc; ++i) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
          return;
        }
      }
    }
  } catch (std::runtime_error &) {
    throw;
  }
}

void Application::exit(int code) {
  if (instancePtr) {
    instancePtr->imp_->exit(code);
  }
}

WindowImpFactory *Application::windowFactory() {
  if (instancePtr && instancePtr->imp_) {
    return instancePtr->imp_->windowFactory();
  }
  return nullptr;
}

EventImpFactory *Application::eventFactory() {
  if (instancePtr && instancePtr->imp_) {
    return instancePtr->imp_->eventFactory();
  }
  return nullptr;
}

void Application::notify(Window *window, std::unique_ptr<Event> event) {
  EventNotifyer::notify(window, std::move(event));
}

void Application::setIterationTimeInterval(std::chrono::milliseconds time) {
  imp_->setIterationTimeInterval(time);
}

std::chrono::milliseconds Application::iterationTimeInterval() const {
  return imp_->iterationTimeInterval();
}

void Application::registerObject(Object *obj) {
  if (instancePtr && instancePtr->imp_) {
    instancePtr->imp_->registerObject(obj);
  }
}

void Application::unregisterObject(Object *obj) {
  if (instancePtr && instancePtr->imp_) {
    instancePtr->imp_->unregisterObject(obj);
  }
}
} // namespace KaliLaska
