// Application.cpp

#include "KaliLaska/Application.hpp"
#include "KaliLaska/Event.hpp"
#include "KaliLaska/EventNotifyer.hpp"
#include "sdl/ApplicationSdl.hpp"
#include <iostream>
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
    imp_ = new ApplicationSdl{};
    parseArguments(argc, argv);
    setUps(DEFAULT_UPS);
  } catch (std::runtime_error &) {
    throw;
  }
}

Application::~Application() {
  delete imp_;
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

void Application::notify(Window *window, std::unique_ptr<Event> event) const {
  EventNotifyer::notify(window, std::move(event));
}

int Application::ups() {
  if (instancePtr && instancePtr->imp_) {
    return instancePtr->imp_->ups();
  }
  return 0;
}

void Application::setUps(int ups) {
  if (instancePtr && instancePtr->imp_) {
    instancePtr->imp_->setUps(ups);
  }
}
} // namespace KaliLaska
