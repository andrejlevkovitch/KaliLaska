// Application.cpp

#include "KaliLaska/Application.hpp"
#include "AppFactory.hpp"
#include "EventNotifyer.hpp"
#include "KaliLaska/Event.hpp"
#include "application/imp/ApplicationImp.hpp"
#include "logger/logger.hpp"
#include <chrono>
#include <stdexcept>
#include <string.h>

#define DEFAULT_UPS 10

namespace KaliLaska {

inline static Application *instancePtr = nullptr;

Application::Application(int argc, char *argv[])
    : imp_{} {
  LOG_TRACE << "Application konstructor";

  if (!instancePtr) {
    instancePtr = this;
  } else {
    LOG_THROW(std::runtime_error, "Application can not be initialized twice");
  }
  try {
    imp_ = AppFactory::createAppImp();
    parseArguments(argc, argv);
  } catch (std::runtime_error &) {
    throw;
  }
}

// brief we need the konstructor here, because only here we now how destroy
// implementation, so we can not mark the destructor as default (in header for
// implementation uses predeclaration)
Application::~Application() {
  LOG_TRACE << "Application: destructor";
}

Application *Application::instance() {
  return instancePtr;
}

int Application::exec() {
  LOG_TRACE << "Application: start main cickle";
  if (instancePtr) {
    return instancePtr->imp_->exec();
  } else {
    LOG_THROW(std::runtime_error, "Application not initialized");
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
  LOG_TRACE << "Application: call exit";
  if (instancePtr) {
    instancePtr->imp_->exit(code);
  }
}

ApplicationImp *Application::implementation() {
  if (instancePtr) {
    return instancePtr->imp_.get();
  }
  return nullptr;
}

void Application::notify(Window *window, std::unique_ptr<Event> event) {
  EventNotifyer::notify(window, std::move(event));
}

void Application::setIterationTimeInterval(std::chrono::milliseconds time) {
  LOG_DEBUG << "Application: set interval to " << time.count()
            << " milliseconds";
  imp_->setIterationTimeInterval(time);
}

std::chrono::milliseconds Application::iterationTimeInterval() const {
  return imp_->iterationTimeInterval();
}

void Application::registerObject(Object *obj) {
  if (instancePtr && instancePtr->imp_) {
    LOG_DEBUG << "Application: object registered " << obj;
    instancePtr->imp_->registerObject(obj);
  }
}

void Application::unregisterObject(Object *obj) {
  if (instancePtr && instancePtr->imp_) {
    LOG_DEBUG << "Application:: object unregistered " << obj;
    instancePtr->imp_->unregisterObject(obj);
  }
}
} // namespace KaliLaska
